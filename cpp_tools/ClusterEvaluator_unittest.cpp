/*
 * =====================================================================================
 *
 *       Filename:  ClusterEvaluator_unittest.cpp
 *
 *    Description:  ClusterEvaluator的单元测试
 *
 *        Version:  1.0
 *        Created:  06/05/2013 09:13:57 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  李海鑫 (xavier), xavier.ssdut@gmail.com
 *        Company:  ssdut.dlut.edu.cn
 *
 * =====================================================================================
 */

#include	<gtest/gtest.h>
#include	"ClusterEvaluator.h"

using machinelearning::ClusterEvaluator;

class ClusterEvaluatorTest : public ::testing::Test
{
protected:
 	static const vector<int> right_clus;
	static const vector<int> test_clus;
};

const vector<int> ClusterEvaluatorTest::right_clus={1,1,1,1,1,1,2,2,2,2,2,2,3,3,3,3,3};
const vector<int> ClusterEvaluatorTest::test_clus={1,2,1,1,1,1,1,2,2,2,2,3,1,1,3,3,3};

TEST_F(ClusterEvaluatorTest, test_mi)
{
	auto mi = ClusterEvaluator::calculateMI(right_clus, test_clus);
	EXPECT_NEAR(0.565445018843, mi, 0.00000001) << "mi=" << mi;
}

TEST_F(ClusterEvaluatorTest, test_nmi)
{
	auto nmi = ClusterEvaluator::calculateNMI(right_clus, test_clus);
	EXPECT_NEAR(0.364561771857, nmi, 0.00000001) << "nmi=" << nmi;
}

TEST_F(ClusterEvaluatorTest, test_entropy)
{
	auto right_entropy = ClusterEvaluator::calculateEntropy(right_clus);
	EXPECT_NEAR(1.57986340107, right_entropy, 0.00000001) << "right_entropy" << right_entropy;

	auto test_entropy = ClusterEvaluator::calculateEntropy(test_clus);
	EXPECT_NEAR(1.52218987217, test_entropy, 0.00000001) << "test_entropy" << test_entropy;
}

TEST_F(ClusterEvaluatorTest, test_purity)
{
	auto purity = ClusterEvaluator::calculatePurity(right_clus, test_clus);
	EXPECT_NEAR(0.705882352941, purity, 0.00000001) << "purity" << purity;
}
