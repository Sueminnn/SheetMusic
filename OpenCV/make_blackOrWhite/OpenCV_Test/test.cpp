

#include "opencv2/imgcodecs.hpp"

#include "opencv2/highgui/highgui.hpp"


using namespace cv;

int main()

{

	//�̹��� ������ �ҷ��� �׷��� �̹����� ��ȯ�Ѵ�.  

	Mat input_gray_image = imread("school.jpg", IMREAD_GRAYSCALE);



	namedWindow("origin", WINDOW_AUTOSIZE);

	namedWindow("gray image", WINDOW_AUTOSIZE);



	Mat result_binary_image;

	//threshold���� 127�� �ؼ� ����ȭ �Ѵ�.

	//�Է� �̹����� Ư�� �ʼ����� threshold������ ũ�� ��� 

	//�̹������� ���� ��ġ�� �ȼ����� 255�� �Ѵ�.

	//thshold������ ���� ��쿡�� 0�� �ȴ�.

	threshold(input_gray_image, result_binary_image, 127, 255, THRESH_BINARY);



	imshow("black or white", result_binary_image);

	imshow("gray image", input_gray_image);



	//�ƹ�Ű�� ���� �� ���� ����Ѵ�.

	while (waitKey(0) < 0);
}