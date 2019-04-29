#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <vector>

#define MAX_PIXEL 255

using namespace cv;

// arr�� �ش��� out_points vector�� ��� �Լ�
void SetLocalMaxPoints(const int* arr, const int arr_size, std::vector<int>& out_points);

int main() {
	Mat music_image;
	int* num_black_x;    // x�࿡�� ���� �ȼ��� �� ���� �迭
	int* num_black_y;    // y�࿡�� ���� �ȼ��� �� ���� �迭
	std::vector<int> points_x;	// x�࿡�� ��ǥ �ִ� ��ǥ(�߾� ����)
	std::vector<int> points_y;	// y�࿡�� ��ǥ �ִ� ��ǥ(�߾� ����)
	std::vector<Point2d> note_points;    // ���� ��ǥ ��ǥ(�߾� ����)

	music_image = imread("dot_image_big.jpg", IMREAD_REDUCED_GRAYSCALE_2);
	// 2bit ��� �̹��� �о����
	
	num_black_x = new int[music_image.cols];
	num_black_y = new int[music_image.rows];

	// ���� pixel count
	std::cout << "y�� ����" << std::endl;
	int line_sum = 0;
	for (int i = 0; i < music_image.rows; i++) {
		for (int j = 0; j < music_image.cols; j++) {
			if (music_image.at<uchar>(i, j) < 125) {
				line_sum += 1;
			}
		}
		/*if (line_sum != 0) {
			std::cout << i << " " << line_sum << std::endl;
		}*/
		num_black_y[i] = line_sum;
		line_sum = 0;
	}
	
	std::cout << "x�� ����" << std::endl;
	line_sum = 0;
	for (int i = 0; i < music_image.cols; i++) {
		for (int j = 0; j < music_image.rows; j++) {
			if (music_image.at<uchar>(j, i) < 125) {
				line_sum += 1;
			}
		}
		/*if (line_sum != 0) {
			std::cout << i << " " << line_sum << std::endl;
		}*/
		num_black_x[i] = line_sum;
		line_sum = 0;
	}
	

	std::cout << "------------------------------" << std::endl;

	std::cout << "y�� ���� �ִ� ��ǥ" << std::endl;
	SetLocalMaxPoints(num_black_y, music_image.rows, points_y);
	std::cout << "count: " << points_y.size() << std::endl;

	std::cout << "x�� ���� �ִ� ��ǥ" << std::endl;
	SetLocalMaxPoints(num_black_x, music_image.cols, points_x);
	std::cout << "count: " << points_x.size() << std::endl;

	// ���� ��ǥ ��ǥ ���ϱ�
	for (int i = 0; i < points_x.size(); i++) {
		for (int j = 0; j < points_y.size(); j++) {
			if (music_image.at<uchar>(points_y[j], points_x[i]) < 125) {
				note_points.push_back(Point(points_x[i], points_y[j]));
				std::cout << points_x[i] << ", " << points_y[j] << std::endl;
			}
		}
	}

	delete[] num_black_x;
	delete[] num_black_y;

	/*
	//�̸� �������ְ�
	namedWindow("MusicDot", WINDOW_AUTOSIZE);
	//�� �̸����� ȭ��â�� ����. 
	imshow("MusicDot", music_image);


	music_image.at<uchar>();
	*/

	while (waitKey(0) > 0) {
	}

	return 0;
}

void SetLocalMaxPoints(const int * arr, const int arr_size, std::vector<int>& out_points)
{
	bool is_rising = false;
	bool is_same = false;
	int same_start = 0;
	int local_max;
	for (int i = 0; i < arr_size - 1; i++) {
		// �ö󰡴� �������� �ش�
		if (arr[i] > arr[i + 1] && is_rising) {
			if (is_same) {
				local_max = int((same_start + i) / 2);
			}
			else {
				local_max = i;
			}
			out_points.push_back(local_max);

			is_rising = false;
			is_same = false;
		}
		else if (arr[i] < arr[i + 1]) {
			is_rising = true;
			is_same = false;
		}
		else if (arr[i] == arr[i + 1] && !is_same) {
			is_same = true;
			same_start = i;
		}

	}
}
