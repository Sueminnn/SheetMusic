#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace cv;

#include <iostream>

using namespace std;

int main()
{
	Mat origin;
	Mat img;
	origin = imread("threeBear.jpg", IMREAD_GRAYSCALE);
	threshold(origin, img, 127, 255, THRESH_BINARY);

	namedWindow("origin", WINDOW_AUTOSIZE);
	imshow("origin", origin);
	
	int line[5] = { -1,-1,-1,-1,-1 };
	int lineSize[5] = { 0,0,0,0,0 };

	int count; // �ش� ���� ������ �ȼ��� ��
	int k; // k��° ����
	int l = 0; // l��° ����
	Mat measure[3]; // ���� 3��
	int gap;
	for (int i = 0; i < img.rows; i++)
	{
		count = 0;
		for (int j = 0; j < img.cols; j++)
		{
			if (!img.at<uchar>(i, j))
			{
				count++;
			}
		}

		if (count / (float)img.cols > 0.6) //������ ��� ��ü ũ�⿡ 0.6�̻� ����
		{
			k = 0;
			while( k < 5)
			{
				if (line[k] == -1)
				{
					break;
				}
				k++;
			}

			if (k == 0)
			{
				line[0] = i;
				lineSize[0]++;
			}
			else if (line[k - 1] + lineSize[k - 1] == i)
			{
				lineSize[k - 1]++;
			}
			else
			{
				line[k] = i;
				lineSize[k]++;
			}
		}
		else if (line[4] != -1) //�������ٿ� ���� ä������ ������ �Ѿ���
		{
			gap = line[1] - line[0];
			Rect rect(0, line[0] - (gap*2) , img.cols, line[4]-line[0] + (gap*5));
			measure[l] = img(rect);
			l++;
			for (int p = 0; p < 5; p++)
			{
				cout << p + 1 << "��° �� ��ǥ : " << line[p] << endl << p + 1 << "��° ���� ���� : " << lineSize[p] << endl << endl;
			}
			for (int m = 0; m < 5; m++)
			{
				line[m] = -1;
				lineSize[m] = 0;
			}
		}
	}
	imwrite("mesure1.jpg", measure[0]);
	imwrite("mesure2.jpg", measure[1]);
	imwrite("mesure3.jpg", measure[2]);


	namedWindow("ù ����", WINDOW_AUTOSIZE);
	imshow("ù ����", measure[0]);
	namedWindow("��° ����", WINDOW_AUTOSIZE);
	imshow("��° ����", measure[1]);
	namedWindow("��° ����", WINDOW_AUTOSIZE);
	imshow("��° ����", measure[2]);



	//Rect rect(0, firstline - gap, img.cols, gap * 9 );
	//Mat subimg = img(rect);

	//imwrite("measure.jpg", subimg);

	while (waitKey(0) < 0);
	return 0;
}