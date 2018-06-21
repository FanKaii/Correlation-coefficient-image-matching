#ifndef CORRELATION_COEFFICIENT_MATCHER_H_
#define CORRELATION_COEFFICIENT_MATCHER_H_

#include <opencv.hpp>
#include <random>

class CorrelationCoefficientMatcher
{
public:
	//����ƥ�������
	class Matcher
	{
	public:
		Matcher() = default;
		Matcher(const cv::Point &pt_l, const cv::Point &pt_r, double index) :m_ptl(pt_l), m_ptr(pt_r), correlationIndex(index) {}

		const cv::Point &getPt_l()const { return m_ptl; }
		const cv::Point &getPt_r()const { return m_ptr; }
		const double &getCorrelationIndex()const { return correlationIndex; }

	private:
		cv::Point m_ptl;   //��Ӱ���ϵĵ�
		cv::Point m_ptr;   //��Ӱ���ϵĵ�

		double correlationIndex = 0;     //���ϵ��
	};

	CorrelationCoefficientMatcher &setWinSize(int width, int height)    //���ô��ڴ�С
	{ 
		m_winWidth = width % 2 == 0 ? width + 1 : width;
		m_winHeight = height % 2 == 0 ? height + 1 : height;

		return *this;
	}

	/*
	* ���õ�ƥ����
	* @ srcImg����Ӱ����֪��λ�ڸ�Ӱ����
	* @ searchImg����Ӱ�񣬳�����Ҫ�ҳ���Ӱ���е���֪���Ӧ����Ӱ���е�ͬ����
	* @ pts_l ����Ӱ���е���֪�����飬������Ҫ�ҳ���Ӱ����ÿ����֪���Ӧ����Ӱ���е�ͬ����
	*/
	const std::vector<Matcher> &detectMatches(const cv::Mat &srcImg, const cv::Mat &searchImg, const std::vector<cv::Point> &pts_l);
	
	//��������ƥ��
	//�����ڶ��̵߳���
	void singleThreadSearch(const cv::Mat &srcImg, const cv::Mat &searchImg, const cv::Point &pt_l);
	
	//���ƥ����
	const std::vector<Matcher> &getMatchers()const { return m_matchers; }

	//��ʾƥ����
	//����ͼ����detectMatches����ͬ
	void drawMatchers(const cv::Mat &srcImg, const cv::Mat &searchImg)const;
private:
	int m_winWidth = 11, m_winHeight = 11;
	std::vector<Matcher> m_matchers;

	//�������ϵ��
	double getCorrelationIndex(const cv::Mat &, const cv::Mat &, const cv::Rect &)const;

	//�жϵ��ǲ��ǿ������㹻�������
	bool isPointLValid(const cv::Mat &, const cv::Point &)const;
};


#endif