#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>
#include <math.h>

using namespace std;
using namespace cv;

struct info
{
	int average;
	int label;
	
};

info train[2400], test[2400];

int temp1[3000][4][4], temp2[3000][4][4], training[2400][4][4], testing[2400][4][4], blocks;
Mat img1, m1, img3,img4, img7, img8;


Mat GenerateM1(Mat img1)
{
	int temp;
	int height = img1.rows - (img1.rows % 4);
	int ht = img1.rows;
	int wt = img1.cols;
	int width = img1.cols - (img1.cols % 4);
	int sum, avg, label;
	int p = 0;
	Mat img2 = img1.clone();
	for (int m = 0; m < height / 2; m += 4)
	{
		for (int n = 0; n < width; n += 4)					
		{
			for (int i = m; i < m + 4; i++)
			{
				for (int j = n; j < n + 4; j++)
				{
					avg = 0, temp = 0;
					for (int x = m; x < m + 4; x++)
					{
						for (int y = n; y < n + 4; y++)
						{
							temp += img1.at<uchar>(x, y);
						}
					}
					avg = temp / 16;
					train[p].average = avg;

					if (avg < 125)
					{
						label = 0;
						train[p].label = label;
					}
					else if (avg >= 125 && avg < 175)
					{
						label = 128;
						train[p].label = label;
					}
					else if (avg >= 175)
					{
						label = 255;
						train[p].label = label;
					}

					train[p].label = label;
					for (int x = m; x < m + 4; x++)
					{
						for (int y = n; y < n + 4; y++)
						{
							img2.at<uchar>(x, y) = label;

						}
					}

				}
			}
			p++;
		}
	}
	return img2;
}

Mat GenerateT1(Mat img1)
{
	int temp;
	int height = img1.rows - (img1.rows % 4);
	int ht = img1.rows;
	int wt = img1.cols;
	int width = img1.cols - (img1.cols % 4);
	int sum, avg, label;
	int p = 0;
	Mat img2 = img1.clone();
	for (int m = img1.rows / 2; m < height; m += 4)
	{
		for (int n = 0; n < width; n += 4)					
		{
			for (int i = m; i < m + 4; i++)
			{
				for (int j = n; j < n + 4; j++)
				{
					avg = 0, temp = 0;
					for (int x = m; x < m + 4; x++)
					{
						for (int y = n; y < n + 4; y++)
						{
							temp += img1.at<uchar>(x, y);
						}
					}
					avg = temp / 16;
					test[p].average = avg;

					if (avg < 125)
					{
						label = 0;
						test[p].label = label;
					}
					else if (avg >= 125 && avg < 175)
					{
						label = 128;
						test[p].label = label;
					}
					else if (avg >= 175)
					{
						label = 255;
						test[p].label = label;
					}

					test[p].label = label;
					for (int x = m; x < m + 4; x++)
					{
						for (int y = n; y < n + 4; y++)
						{
							img2.at<uchar>(x, y) = label;

						}
					}

				}
			}
			p++;
		}
	}
	namedWindow("T1", CV_WINDOW_AUTOSIZE);
	imshow("T1", img2);
	waitKey(0);
	cvDestroyAllWindows();
	return img2;
	
}

void Top(Mat img1, int temp1[2400][4][4])
{
	int temp;
	int height = img1.rows - (img1.rows % 4);
	int ht = img1.rows;
	int wt = img1.cols;
	int x1, y1;
	int width = img1.cols - (img1.cols % 4);
	int sum, avg, label;
	int p = 0;
	Mat img2 = img1.clone();
	for (int m = 0; m < height / 2; m += 4)
	{
		for (int n = 0; n < width; n += 4)					
		{
			for (int i = m; i < m + 4; i++)
			{
				for (int j = n; j < n + 4; j++)
				{
					avg = 0, temp = 0, x1 = 0;
					for (int x = m; x < m + 4; x++)
					{
						y1 = 0;
						for (int y = n; y < n + 4; y++)
						{
							temp1[p][x1][y1] = img1.at<uchar>(x, y);
							y1++;
							temp += img1.at<uchar>(x, y);
						}
						x1++;
					}
					avg = temp / 16;
					train[p].average = avg;

					if (avg < 125)
					{
						label = 0;
						train[p].label = label;
					}
					else if (avg >= 125 && avg < 175)
					{
						label = 128;
						train[p].label = label;
					}
					else if (avg >= 175)
					{
						label = 255;
						train[p].label = label;
					}

					train[p].label = label;
				}
			}
			p++;
		}
	}
	
}

void Bottom(Mat img1, int temp1[2400][4][4])
{
	int temp;
	int height = img1.rows - (img1.rows % 4);
	int ht = img1.rows;
	int wt = img1.cols;
	int x1, y1;
	int width = img1.cols - (img1.cols % 4);
	int sum, avg, label;
	int p = 0;
	Mat img2 = img1.clone();
	for (int m = img1.rows / 2; m < height; m += 4)
	{
		for (int n = 0; n < width; n += 4)					
		{
			for (int i = m; i < m + 4; i++)
			{
				for (int j = n; j < n + 4; j++)
				{
					avg = 0, temp = 0, x1 = 0;
					for (int x = m; x < m + 4; x++)
					{
						y1 = 0;
						for (int y = n; y < n + 4; y++)
						{
							temp1[p][x1][y1] = img1.at<uchar>(x, y);
							y1++;
							temp += img1.at<uchar>(x, y);
						}
						x1++;
					}
					avg = temp / 16;
					test[p].average = avg;

					if (avg < 125)
					{
						label = 0;
						test[p].label = label;
					}
					else if (avg >= 125 && avg < 175)
					{
						label = 128;
						test[p].label = label;
					}
					else if (avg >= 175)
					{
						label = 255;
						test[p].label = label;
					}

					test[p].label = label;
				}
			}
			p++;
		}
	}
	

}

Mat GenerateN1(Mat img1, int temp1[2400][4][4], int temp2[2400][4][4], int blocks)
{
	Mat img2 = img1.clone();
	int mean, avg, temp, sum, classID, p;

	for (int i = 0; i < blocks; i++)
	{
		mean = 128;
		for (int j = 0; j < blocks; j++)
		{
			avg = 0, temp = 0;
			for (int k = 0; k < 4; k++)
			{
				for (int l = 0; l < 4; l++)
				{
					temp += pow(temp1[j][k][l] - temp2[i][k][l], 2);
				}
			}
			sum = sqrt(temp);
			avg = sum / 16;
			if (avg < mean)
			{
				mean = avg;
				classID = j;
			}

		}
		for (int x = 0; x < 4; x++)
		{
			for (int y = 0; y < 4; y++)
			{
				temp2[i][x][y] = temp1[classID][x][y];		
			}
		}
	}

	int xx, yy;
	int height = img1.rows - (img1.rows % 4);
	int width = img1.cols - (img1.cols % 4);

	p = 0;
	for (int m = height / 2; m < height; m += 4)
	{
		for (int n = 0; n < width; n += 4)					
		{
			for (int i = m; i < m + 4; i++)
			{
				for (int j = n; j < n + 4; j++)
				{
					xx = 0;
					for (int x = m; x < m + 4; x++)
					{
						yy = 0;
						for (int y = n; y < n + 4; y++)
						{
							img2.at<uchar>(x, y) = temp2[p][xx][yy];
						}
					}
				}
			}
			p++;
		}
	}
	return img2;
}

Mat GenerateN2(Mat img1, int temp1[2400][4][4], int temp2[2400][4][4], int blocks)
{
	Mat img2 = img1.clone();
	int classID = 0, count = 0;
	unsigned int distance, new_distance = 255;
	for (int i = 0; i < blocks; i++)
	{
		distance = 255;
		for (int j = 0; j < blocks; j++)
		{
			new_distance = 255;
			new_distance = train[j].average - test[i].average;
			if (new_distance < distance)
			{
				distance = new_distance;
				classID = j;
			}

		}

		for (int k = 0; k < 4; k++)
		{
			for (int l = 0; l < 4; l++)
			{
				temp2[i][k][l] = temp1[classID][k][l];
				
			}
		}
	}

	int height = img1.rows - (img1.rows % 4);
	int width = img1.cols - (img1.cols % 4);
	int xx, yy;
	int p = 0;
	for (int m = height / 2; m < height; m += 4)
	{
		for (int n = 0; n < width; n += 4)					
		{
			for (int i = m; i < m + 4; i++)
			{
				for (int j = n; j < n + 4; j++)
				{
					xx = 0;
					for (int x = m; x < m + 4; x++)
					{
						yy = 0;
						for (int y = n; y < n + 4; y++)
						{
							img2.at<uchar>(x, y) = temp2[p][xx][yy];
						}
					}
				}
			}
			p++;
		}
	}

	return img2;
}

Mat GenerateN3(Mat img1, int temp1[2400][4][4], int temp2[2400][4][4], int blocks)
{
	Mat img2 = img1.clone();
	int classID = 0, count = 0;
	unsigned int distance, new_distance = 255;
	for (int i = 0; i < blocks; i++)
	{
		distance = 255;
		for (int j = 0; j < blocks; j++)
		{
			new_distance = 255;
			new_distance = train[j].average - test[i].average;
			if (new_distance < distance)
			{
				distance = new_distance;
				classID = j;
			}

		}

		for (int k = 0; k < 4; k++)
		{
			for (int l = 0; l < 4; l++)
			{
				temp2[i][k][l] = train[classID].average;
				
			}
		}
	}

	int height = img1.rows - (img1.rows % 4);
	int width = img1.cols - (img1.cols % 4);
	int xx, yy;
	int p = 0;
	for (int m = height / 2; m < height; m += 4)
	{
		for (int n = 0; n < width; n += 4)					
		{
			for (int i = m; i < m + 4; i++)
			{
				for (int j = n; j < n + 4; j++)
				{
					xx = 0;
					for (int x = m; x < m + 4; x++)
					{
						yy = 0;
						for (int y = n; y < n + 4; y++)
						{
							img2.at<uchar>(x, y) = temp2[p][xx][yy];
						}
					}
				}
			}
			p++;
		}
	}

	return img2;
}

int Average(int m)
{
	int i = 0;
	int temp = 0, avg;
	while (i < 2400)
	{
		if (train[i].label == m)
		{
			temp += train[i].average;
		}
		i++;
	}
	avg = temp / i;
	return avg;
}

Mat GenerateN4(Mat img1, int temp1[2400][4][4], int temp2[2400][4][4], int blocks)
{
	Mat img2 = img1.clone();
	int classID = 0, count = 0, matching_label, cumulative_avg;
	unsigned int distance, new_distance = 255;
	for (int i = 0; i < blocks; i++)
	{
		distance = 255;
		for (int j = 0; j < blocks; j++)
		{
			new_distance = 255;
			new_distance = train[j].average - test[i].average;
			if (new_distance < distance)
			{
				distance = new_distance;
				classID = j;
			}

		}

		matching_label = train[classID].label;
		cumulative_avg = Average(matching_label);

		for (int k = 0; k < 4; k++)
		{
			for (int l = 0; l < 4; l++)
			{
				temp2[i][k][l] = cumulative_avg;
			}
		}
	}

	int height = img1.rows - (img1.rows % 4);
	int width = img1.cols - (img1.cols % 4);
	int xx, yy;
	int p = 0;
	for (int m = height / 2; m < height; m += 4)
	{
		for (int n = 0; n < width; n += 4)				
		{
			for (int i = m; i < m + 4; i++)
			{
				for (int j = n; j < n + 4; j++)
				{
					xx = 0;
					for (int x = m; x < m + 4; x++)
					{
						yy = 0;
						for (int y = n; y < n + 4; y++)
						{
							img2.at<uchar>(x, y) = temp2[p][xx][yy];
						}
					}
				}
			}
			p++;
		}
	}

	return img2;
}


void K1(Mat img1)
{
	Mat img2 = img1.clone();
	int height = img1.rows;
	int width = img1.cols;

	for ( int i = 0; i < height/2; i++ )
	{
	for ( int j = 0; j < width; j++ )
	{
	if ( img1.at<uchar>(i, j) > 0 && img1.at<uchar>(i, j) <= 85 )
	img2.at<uchar>(i, j) = 0;
	else if ( img1.at<uchar>(i, j) > 85 && img1.at<uchar>(i, j) <= 170 )
	img2.at<uchar>(i, j) = 128;
	else if( img1.at<uchar>(i, j) > 170 && img1.at<uchar>(i, j) <= 255 )
	img2.at<uchar>(i, j) = 255;
	}
	}

	imshow("K-means", img2);
	waitKey(0);
	cvDestroyAllWindows();

}


void n1(Mat img1)
{
	Mat M1 = img1.clone();
	M1 = GenerateM1(img1);
	
	blocks = ((img1.rows / 2) / 4) * (img1.cols / 4);
	Top(M1, training);
	Bottom(M1, testing);
	Mat N1 = img1.clone();
	N1 = GenerateN1(M1, training, testing, blocks);

	imshow("N1", N1);
	waitKey(0);
	cvDestroyAllWindows();
	float error = 0;
	float no_of_different_averages = 0;
	float no_of_same_averages = 0;
	float no_of_different_labels = 0;
	float no_of_same_labels = 0;
	for (int i = 0; i < blocks; i++)
	{

		if (train[i].average != test[i].average)
			no_of_different_averages++;
		else if (train[i].average == test[i].average)
			no_of_same_averages++;

		if (train[i].label != test[i].label)
			no_of_different_labels++;
		else if (train[i].label == test[i].label)
			no_of_same_labels++;

	}

	error = (no_of_different_labels / blocks) * 100;
	cout <<"Error Rate:"<< error << endl;
}


void n2(Mat img1)
{
	blocks = ((img1.rows / 2) / 4) * (img1.cols / 4);
	Top(img1, training);
	Bottom(img1, testing);
	Mat N2 = img1.clone();
	N2 = GenerateN2(img1, training, testing, blocks);
	imshow("N2", N2);
	waitKey(0);
	cvDestroyAllWindows();
	
}


void n3(Mat img1)
{
	blocks = ((img1.rows / 2) / 4) * (img1.cols / 4);
	Top(img1, training);
	Bottom(img1, testing);
	Mat N3 = img1.clone();
	N3 = GenerateN3(img1, training, testing, blocks);
	imshow("N3", N3);
	waitKey(0);
	cvDestroyAllWindows();
}

Mat difference(Mat im1, Mat im2, Mat im3){

	absdiff(im1, im2, im3);
	imshow("ABSOLUTE DIFFERENCE BETWEEN 2 FRAMES", im3);
	waitKey(0);
	cvDestroyAllWindows();
	return im3;

}

void thresh_diff(Mat im1, Mat im2){

	threshold(im1, im2, 128, 255, THRESH_BINARY);
	imshow("THRESHOLDED DIFFERENCE BETWEEN 2 FRAMES", im2);
	waitKey(0);
	cvDestroyAllWindows();
}

static void drawOptFlowMap(const Mat& flow, Mat& cflowmap, int step,
                    double, const Scalar& color, int temp)
{
    for(int y = 0; y < cflowmap.rows; y += step)
        for(int x = 0; x < cflowmap.cols; x += step)
        {
            const Point2f& fxy = flow.at<Point2f>(y, x);
	    if (temp == 0){
            line(cflowmap, Point(x,y), Point(cvRound(x+fxy.x), cvRound(y+fxy.y)),
                 color);
	    }
	    if (temp == 1){
            line(cflowmap, Point(x,y), Point(cvRound(x+fxy.x), cvRound(y+fxy.y)),
                 CV_RGB(255, 0, 0));
	    }
 
            circle(cflowmap, Point(x,y), 2, color, -1);
        }
}

int main(int argc, char *argv[])
{
	img1 = imread("test.bmp", 0);
	int choice;
	bool menu = true;
	while (menu != false) {
	cout << "\n\n************************************************************************************************\n";
	cout << " 1 - M1\n";
	cout << " 2 - N1\n";
	cout << " 3 - N2\n";
	cout << " 4 - N3\n";
	cout << " 5 - N4\n";
	cout << " 6 - T1\n";
	cout << " 7 - K1\n";
	cout << " 8 - Motion Vectors across image frames\n";
	cout << " 9 - Difference between 2 frames\n";
	cout << " 10 - optical flow for each pixel(optional)\n";	
	cout << " 11 - EXIT\n";	
	cout << "************************************************************************************************\n";
	cout << " ENTER YOUR CHOICE AND PRESS RETURN: ";

	cin >> choice;

	switch(choice)
	{
	case 1:
	{
	m1 = GenerateM1(img1);
	imshow("M1", m1);
	waitKey(0);
	cvDestroyAllWindows();
	} 
	break;
	case 2:
	{
	n1(m1);
	}
	break;
	case 3:
	{
	n2(img1);
	}
	break;
	case 4:
	{
	n3(img1);
	}
	break;
	case 5:
	{
	blocks = ((img1.rows / 2) / 4) * (img1.cols / 4);
	Top(img1, training);
	Bottom(img1, testing);
	Mat N4 = img1.clone();
	N4 = GenerateN4(img1, training, testing, blocks);

	namedWindow("N4", CV_WINDOW_AUTOSIZE);
	imshow("N4", N4);
	waitKey(0);
	cvDestroyAllWindows();
	}
	break;
	case 6:
	{
	GenerateT1(img1);
	}
	break;
	case 7:
	{
	K1(img1);
	waitKey();
	}
	break;
	
	case 8:
	{
	Mat img, gray, prevgray, flow, cflow;
	if(
	  (!(img = imread( "2.bmp", CV_LOAD_IMAGE_COLOR)).empty()))
	    {
		  cvtColor(img, gray, CV_BGR2GRAY);
  
		  prevgray = imread("1.bmp",0);

		  if(!prevgray.empty())
		  {
		    calcOpticalFlowFarneback(prevgray, gray, flow, 0.5, 3, 15, 3, 5, 1.2, 0);
		    cvtColor(prevgray, cflow, CV_GRAY2BGR);
		    drawOptFlowMap(flow, cflow, 8, 1.5, CV_RGB(0, 255, 0), 0);

		    imshow("Motion Vectors", cflow);
		    waitKey(0);
		    cvDestroyAllWindows();
		  }

		  std::swap(prevgray, gray);
	  }	
		
	}
	break;
	
	case 9:
	{
	   
	    Mat m, n;
	    Mat img1 = imread("1.bmp",0);
	    Mat img2 = imread("2.bmp",0);

		
            Mat img5 = imread("3.bmp", 0);
	    Mat img6 = imread("4.bmp", 0);

	    if (img1.empty() || img2.empty() || img5.empty() || img6.empty())
	    {
		cout << "Read error" << endl;
		return -1;
	    }

	    img3 = difference(img1,img2,m);
	    thresh_diff(img3,img4);
	
	    img7 = difference(img5,img6,n);
	    thresh_diff(img7,img8);
	    
	}
	break;
	case 10:
	{
	Mat img, gray, prevgray, flow, cflow;
	if(
	  (!(img = imread( "2.bmp", CV_LOAD_IMAGE_COLOR)).empty()))
	    {
		  cvtColor(img, gray, CV_BGR2GRAY);
  
		  prevgray = imread("1.bmp",0);

		  if(!prevgray.empty())
		  {
		    calcOpticalFlowFarneback(prevgray, gray, flow, 0.5, 3, 15, 3, 5, 1.2, 0);
		    cvtColor(prevgray, cflow, CV_GRAY2BGR);
		    drawOptFlowMap(flow, cflow, 2, 1.5, CV_RGB(0, 255, 0), 1);

		    imshow("Optical flow", cflow);
		    waitKey(0);
		    cvDestroyAllWindows();
		  }

		  std::swap(prevgray, gray);
	  }	
		
	}
	break;
	case 11:
     	{
 	cout << "\n\nEXITING..\n\n";
 	menu = false;
     	}
 	break;

 default:
     {
	cout << "NOT A VALID CHOICE. \n";
	cout << "PLEASE CHOOSE AGAIN.\n";
	cin >> choice;
     }
  break;
	}
	}
}
