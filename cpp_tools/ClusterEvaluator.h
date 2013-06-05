/*
 * =====================================================================================
 *
 *       Filename:  ClusterEvaluator.h
 *
 *    Description:  提供几种簇评估方法的类
 *
 *        Version:  1.0
 *        Created:  06/04/2013 10:30:26 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  李海鑫 (xavier), xavier.ssdut@gmail.com
 *        Company:  ssdut.dlut.edu.cn
 *
 * ===================================================================================== */
#pragma once


#include	<vector>

using std::vector;

namespace machinelearning{

class ClusterEvaluator
{
public:
	/**
	 * @brief	计算两个聚类结果的归一化互信息(nmi)
	 * @standard_cluster_result	标准的聚类结果
	 * @test_cluster_result		需要评价的聚类结果，
	 *							每个数据节点的排列需要与标准的聚类结果一一对应
	 * @return	返回test_cluster相对right_cluster的nmi值
	 */
	static double calculateNMI(const vector<int>& standard_cluster_result, 
							    const vector<int>& test_cluster_result );

	/**
	 * @brief	计算两个聚类结果的互信息(mi)
	 * @standard_cluster_result	标准的聚类结果
	 * @test_cluster_result		需要评价的聚类结果，
	 *							每个数据节点的排列需要与标准的聚类结果一一对应
	 * @return	返回test_cluster相对right_cluster的nmi值
	 */
	static double calculateMI(const vector<int>& standard_cluster_result, 
							   const vector<int>& test_cluster_result );

	/**
	 * @brief	计算一个vector中的entropy
	 * @arr		需要计算熵的vector
	 * @return	arr的entropy
	 */
	static double calculateEntropy(const vector<int>& arr);

	/**
	 * @brief	计算聚类结果的纯度(purity)
	 * @standard_cluster_result	标准的聚类结果
	 * @test_cluster_result		需要评价的聚类结果，
	 *							每个数据节点的排列需要与标准的聚类结果一一对应
	 * @return	返回test_cluster相对right_cluster的purity
	 */
	static double calculatePurity(const vector<int>& standard_cluster_result, 
							   const vector<int>& test_cluster_result );

private:
	/**
	 * @brief	私有方法，考虑到多处对unique vector都有需求,就加了这个方法
	 * @clus_res	传出参数，函数调用结束后，它就变成unique vector了
	 * @return	得到的unique vector
	 */
	static vector<int>& __toUniqueVector(vector<int>& clus_res);

	/**
	 * @brief	私有方法，返回vector arr中所有value等于w的下表集合
	 * @w		传入参数, 
	 * @arr		传入参数，
	 * @result_index_arr	传出参数
	 * @return	得到的result_index_arr
	 */
	static vector<int>& __getWInArrIndex(const int& w, const vector<int>& arr,
								vector<int>& result_index_arr);

	/**
	 * @brief	私有方法，返回两个vector的交集
	 * @a_arr	传出参数, 会被排序
	 * @b_arr	传出参数, 会被排序
	 * @res_arr	传出参数
	 * @return	res_arr:两个vector的交集
	 */
	static vector<int>& __getInterSection(vector<int>& a_arr, vector<int>& b_arr, 
										vector<int>& res_arr);
};

}
