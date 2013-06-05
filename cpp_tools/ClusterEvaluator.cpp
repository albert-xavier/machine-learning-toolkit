/*
 * =====================================================================================
 *
 *       Filename:  ClusterEvaluator.cpp
 *
 *    Description:  提供几种簇评估方法的类
 *
 *        Version:  1.0
 *        Created:  06/04/2013 11:08:03 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  李海鑫 (xavier), xavier.ssdut@gmail.com
 *        Company:  ssdut.dlut.edu.cn
 *
 * =====================================================================================
 */

#include	<float.h>
#include	<algorithm>
#include	<iterator>
#include	<cmath>
#include	"ClusterEvaluator.h"

namespace machinelearning{

double ClusterEvaluator::calculateNMI(const vector<int>& standard_cluster_result,
									   const vector<int>& test_cluster_result) 
{
	auto I = ClusterEvaluator::calculateMI(standard_cluster_result, test_cluster_result);
	auto H_x = ClusterEvaluator::calculateEntropy(standard_cluster_result);
	auto H_y = ClusterEvaluator::calculateEntropy(test_cluster_result);

	return I/((H_x+H_y)/2.0);
}

double ClusterEvaluator::calculateMI(const vector<int>& standard_cluster_result,
								      const vector<int>& test_cluster_result) 
{
	auto N = standard_cluster_result.size();
	auto I = 0.0;

	//先求出standard_cluster_result和test_cluster_result的unique
	auto tmp_std_clus_res(standard_cluster_result);
	auto tmp_test_clus_res(test_cluster_result);
	ClusterEvaluator::__toUniqueVector(tmp_std_clus_res);
	ClusterEvaluator::__toUniqueVector(tmp_test_clus_res);

	//以下代码参考求互信息的公式
	vector<int> clus_w_set;
	vector<int> clus_j_set;
	vector<int> tmp_intersection;
	for (auto test_clus_w : tmp_test_clus_res)
	{
		for (auto std_clus_j : tmp_std_clus_res)
		{
			__getWInArrIndex(test_clus_w, test_cluster_result, clus_w_set);
			__getWInArrIndex(std_clus_j, standard_cluster_result, clus_j_set);
			tmp_intersection = __getInterSection(clus_w_set, clus_j_set, tmp_intersection);
			auto wk_cj_l2 = tmp_intersection.size() + DBL_MIN; //得到了|Wk ∩ Cj|
			auto wk_l2 = clus_w_set.size();
			auto cj_l2 = clus_j_set.size();
			I += wk_cj_l2/N * ::log2( (wk_cj_l2*N)/(wk_l2*cj_l2) );
		}
	}

	return I;
}

double ClusterEvaluator::calculateEntropy(const vector<int>& arr)
{
	auto H=0.0;
	auto N=arr.size();
	auto uniq_arr(arr);
	ClusterEvaluator::__toUniqueVector(uniq_arr);

	for (const int k : uniq_arr)
	{
		auto wk_l2 = 0.0;
		for (const int i : arr)
		{
			if (i == k)
			{
				wk_l2 += 1.0;
			}
		}
		H += -(wk_l2/N)*::log2(wk_l2/N);
	}

	return H;
}

vector<int>& ClusterEvaluator::__toUniqueVector(vector<int>& clus_res)
{
	std::sort(clus_res.begin(), clus_res.end());
	clus_res.erase(std::unique(clus_res.begin(), clus_res.end()),  clus_res.end());
	return clus_res;
}

vector<int>& ClusterEvaluator::__getWInArrIndex(const int& w, const vector<int>& arr, 
										vector<int>& result_index_arr)
{
	result_index_arr.clear();

	for(auto it = arr.begin(); it != arr.end() ; it ++ )
	{
		if (*it == w)
		{
			result_index_arr.push_back(it-arr.begin());
		}
	}
	return result_index_arr;
}

vector<int>& ClusterEvaluator::__getInterSection(vector<int>& a_arr, vector<int>& b_arr,
										vector<int>& res_arr)
{
	res_arr.clear();
	std::sort(a_arr.begin(), a_arr.end());
	std::sort(b_arr.begin(), b_arr.end());
	std::set_intersection(a_arr.begin(), a_arr.end(), 
						  b_arr.begin(), b_arr.end(),
						  std::back_insert_iterator<vector<int> >(res_arr));
	return res_arr;
}

double ClusterEvaluator::calculatePurity(const vector<int>& standard_cluster_result,
									   const vector<int>& test_cluster_result) 
{
	auto N = standard_cluster_result.size();
	auto p = 0.0;
	auto uniq_test_clus(test_cluster_result);
	auto uniq_std_clus(standard_cluster_result);
	ClusterEvaluator::__toUniqueVector(uniq_test_clus);
	ClusterEvaluator::__toUniqueVector(uniq_std_clus);

	vector<int> clus_wk_set;
	vector<int> clus_cj_set;
	vector<int> tmp_intersection;

	for (auto k : uniq_test_clus)
	{
		auto max_wk_cj_l2 = DBL_MIN;
		for (auto j : uniq_std_clus)
		{
			__getWInArrIndex(k, test_cluster_result, clus_wk_set);
			__getWInArrIndex(j, standard_cluster_result, clus_cj_set);
			__getInterSection(clus_wk_set, clus_cj_set, tmp_intersection);
			if (max_wk_cj_l2 < tmp_intersection.size())
			{
				max_wk_cj_l2 = tmp_intersection.size();
			}
		}
		p += max_wk_cj_l2;
	}

	return p/N;
}

}
