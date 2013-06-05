#!/usr/bin/python
#-*-coding:UTF-8-*-

from numpy import *

def mutual_info(o_arr, c_arr):
	"""	传入参数是两个numpy.array
		o_arr是需要评价的聚类结果
		c_arr是标准的聚类结果
	"""
	N=double(c_arr.size)
	I=0.0
	eps = finfo(float).eps #下面会出现wk_cj_l2为0的情况，直接计算log2会除0异常
	for k in unique(o_arr):
		for j in unique(c_arr):
			wk_arr=(k==o_arr).nonzero()[0]
			cj_arr=(j==c_arr).nonzero()[0]
			wk_cj_l2=double(intersect1d(wk_arr, cj_arr).size) + eps
			wk_l2=double(wk_arr.size)
			cj_l2=double(cj_arr.size)
			I+=(wk_cj_l2/N) * log2( (N*wk_cj_l2)/(wk_l2*cj_l2) )
	return I

def entropy(arr):
	"""	传入参数是一个numpy.array
		返回array中的熵
	"""
	H=0.0
	N=double(arr.size)
	for k in unique(arr):
		wk_l2=double((k==arr).nonzero()[0].size)
		H+= -(wk_l2/N * log2(wk_l2/N))
	return H

def normalized_mutual_info(o_arr, c_arr):
	"""	传入参数是两个numpy.array
		o_arr是需要评价的聚类结果
		c_arr是标准的聚类结果
	"""
	I=mutual_info(o_arr, c_arr)
	H_o_arr=entropy(o_arr)
	H_c_arr=entropy(c_arr)
	return I/((H_o_arr+H_c_arr)/2.0)

def purity(o_arr, c_arr):
	"""	传入参数是两个numpy.array
		o_arr是需要评价的聚类结果
		c_arr是标准的聚类结果
		返回聚类结果的纯度
	"""
	N=double(c_arr.size)
	p=0.0
	for k in unique(o_arr):
		max_wk_cj_l2 = finfo(float).eps
		for j in unique(c_arr):
			wk_arr=(k==o_arr).nonzero()[0]
			cj_arr=(j==c_arr).nonzero()[0]
			wk_cj_l2=double(intersect1d(wk_arr, cj_arr).size)
			if wk_cj_l2 > max_wk_cj_l2:
				max_wk_cj_l2 = wk_cj_l2
		p+=max_wk_cj_l2
	return p/N

if __name__=="__main__":
	c_arr = array([1,1,1,1,1,1,2,2,2,2,2,2,3,3,3,3,3])
	o_arr = array([1,2,1,1,1,1,1,2,2,2,2,3,1,1,3,3,3])
	print normalized_mutual_info(o_arr, c_arr)
	print mutual_info(o_arr, c_arr)
	print entropy(c_arr)
	print entropy(o_arr)
	print purity(o_arr, c_arr)
