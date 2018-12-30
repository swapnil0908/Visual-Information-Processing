#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>
#include <math.h>

 using namespace cv;
 using namespace std;
  


void clear(Mat img){

	for(int i=0;i<img.rows;i++){
		for(int j=0;j<img.cols;j++)
		{
		      img.at<Vec3b>(i, j)[0] = 0;
		      img.at<Vec3b>(i, j)[1] = 0;
		      img.at<Vec3b>(i, j)[2] = 0;
		}
	}
}

float min(int array[3]){

	int min = array[0];
	for(int i=0;i<3;i++){	
		if(min > array[i])
			min = array[i];
	}
	
	return min;
}

int calculate(int b, int g, int r){

  int temp = acos(0.5 * ((r - g) + (r - b)) / sqrt(((r - g)*(r - g)) + ((r - b)*(g - b))));
	
  return temp;

}

Mat HSI(Mat BGR){
	
	Mat hsi = BGR.clone();
	clear(hsi);
	
        float r, g, b;

	for(int i = 0; i < BGR.rows; i++)
    	{
	      for(int j = 0; j < BGR.cols; j++)
		{
		  b = BGR.at<Vec3b>(i, j)[0];
		  g = BGR.at<Vec3b>(i, j)[1];
		  r = BGR.at<Vec3b>(i, j)[2];

		  hsi.at<Vec3b>(i, j)[2] = (b + g + r) / 3;
		}
	}

	
	return hsi;

}


Mat DCT(Mat image_in) {

	
	Mat image_dct = image_in.clone();


	clear(image_dct);
	


	int height = image_in.rows - (image_in.rows % 8);
	int width = image_in.cols - (image_in.cols % 8);
	float temp;
	double alphai, alphaj;
	for (int r = 0; r < height; r += 8)
	{
		for (int c = 0; c < width; c += 8)
		{
			for (int i = r; i < r + 8; i++)
			{
				for (int j = c; j < c + 8; j++)
				{

					temp = 0.0;
					if (i == 0) alphai = 1.0 / sqrt(2.0); else alphai = 1.0;
					if (j == 0) alphaj = 1.0 / sqrt(2.0); else alphaj = 1.0;
					for (int x = r; x < r + 8; x++)
					{
						for (int y = c; y < c + 8; y++)
						{
							temp += (image_in.at<Vec3b>(x, y)[2])
								*(cos((((2 * x) + 1)) * ((i *M_PI)) / (2 * 8)))
								*(cos((((2 * y) + 1)) * ((j *M_PI)) / (2 * 8)));
						}
					}
					temp *= ((2 / sqrt(8 * 8)))*(alphai * alphaj);
					image_dct.at<Vec3b>(i, j)[2] = int(temp);
				}
			}
		}
	}

	return image_dct;

}

Mat IDCT(Mat image_in) {
	int height = image_in.rows - (image_in.rows % 8);
	int width = image_in.cols - (image_in.cols % 8);
	float temp;
	double alphai, alphaj;

	Mat image_idct = image_in.clone();
	
	clear(image_idct);
	
	for (int r = 0; r < height; r += 8)
	{
		for (int c = 0; c < width; c += 8)
		{
			for (int i = r; i < r + 8; i++)
			{
				for (int j = c; j < c + 8; j++)
				{

					temp = 0.0;
					if (i == 0) alphai = 1.0 / sqrt(2.0); else alphai = 1.0;
					if (j == 0) alphaj = 1.0 / sqrt(2.0); else alphaj = 1.0;
					for (int x = r; x < r + 8; x++)
					{
						for (int y = c; y < c + 8; y++)
						{

							temp += (image_in.at<Vec3b>(x, y)[2])
								*(cos((((2 * i) + 1)) * ((x * M_PI)) / (2 * 8)))
								*(cos((((2 * j) + 1)) * ((y * M_PI)) / (2 * 8)))
								*(alphai*alphaj);
						}
					}
					temp *= ((2 / sqrt(8 * 8)));
					image_idct.at<Vec3b>(i, j)[2] = int(temp);
				}
			}
		}
	}


	return image_idct;
}

Mat DCT_DC(Mat image_in) {

	int height = image_in.rows - (image_in.rows % 8);
	int width = image_in.cols - (image_in.cols % 8);
	Mat image_dc(image_in.rows, image_in.cols, image_in.type());
	image_dc = image_in.clone();
	//clear(image_dct_dc);
	for (int r = 0; r < height; r += 8)
	{
		for (int c = 0; c < width; c += 8)
		{
			for (int i = r; i < r + 8; i++)
			{
				for (int j = c; j < c + 8; j++)
				{

					for (int x = r; x < r + 8; x++)
					{
						for (int y = c; y < c + 8; y++)
						{
							if (i == r && j == c)
							{
								image_dc.at<Vec3b>(i, j)[2] = image_dc.at<Vec3b>(i, j)[2];
							}
							else
							{
								image_dc.at<Vec3b>(i, j)[2] = 0;
							}
						}
					}

				}
			}
		}
	}
	return image_dc;
}

Mat DCT_9(Mat image_in) {

	int height = image_in.rows - (image_in.rows % 8);
	int width = image_in.cols - (image_in.cols % 8);

	Mat image_f9(image_in.rows, image_in.cols, image_in.type());
	clear(image_f9);
	image_f9 = image_in.clone();
	for (int r = 0; r < height; r += 8)
	{
		for (int c = 0; c < width; c += 8)
		{
			for (int i = r; i < r + 8; i++)
			{
				for (int j = c; j < c + 8; j++)
				{

					for (int x = r; x < r + 8; x++)
					{
						for (int y = c; y < c + 8; y++)
						{
							if (i == r && j == c || i == r && j == c + 1 || i == r && j == c + 2 || i == r && j == c + 3 || i == r + 1 && j == c || i == r + 1 && j == c + 1 || i == r + 1 && j == c + 2 || i == r + 2 && j == c || i == r + 2 && j == c + 1)
							{
								image_f9.at<Vec3b>(i, j)[2] = image_f9.at<Vec3b>(i, j)[2];
							}
							else
							{
								image_f9.at<Vec3b>(i, j)[2] = 0;
							}
						}
					}

				}
			}
		}
	}
	return image_f9;
}

int xGradient(Mat image, int x, int y)
{
    return image.at<Vec3b>(y-1, x-1)[2] + 2*image.at<Vec3b>(y, x-1)[2] +image.at<Vec3b>(y+1, x-1)[2] -image.at<Vec3b>(y-1, x+1)[2] -2*image.at<Vec3b>(y, x+1)[2] - image.at<Vec3b>(y+1, x+1)[2];
}
 
int yGradient(Mat image, int x, int y)
{
    return image.at<Vec3b>(y-1, x-1)[2] + 2*image.at<Vec3b>(y-1, x)[2] + image.at<Vec3b>(y-1, x+1)[2] - image.at<Vec3b>(y+1, x-1)[2] - 2*image.at<Vec3b>(y+1, x)[2] - image.at<Vec3b>(y+1, x+1)[2];
}


void sobel(Mat img, String name){
	Mat img1 = img.clone();
	int gx, gy, sum;
	clear(img1);
	for(int y = 1; y < img.rows - 1; y++){
	      for(int x = 1; x < img.cols - 1; x++){
		gx = xGradient(img, x, y);

		gy = yGradient(img, x, y);
		
		
		sum = abs(gx) + abs(gy);
		if(sum>255)
		  sum=255;
		else if(sum<0)
		  sum=0;
		img1.at<Vec3b>(y, x)[2]= sum;
	      }
	  }

	imshow(name, img1);
        waitKey(0);
        
        cvDestroyAllWindows();

}




int main(int argc, char **argv) {  
  
  Mat BGR, hsi1, dct1, idct1,idct2, dc1, dc9;

  string image_name1, image_name2;
  int choice;
  bool menu = true;
  while (menu != false) {
	cout << "\n\n************************************************************************************************\n";
	cout << " 1 - LOAD AND DISPLAY THE IMAGE f1 (BASEL3.BMP).\n";
	cout << " 2 - CONVERT ABOVE RGB IMAGE TO HSI AND DISPLAY THE INTENSITY IMAGE\n";
	cout << " 3 - 8x8 DCT\n";
	cout << " 4 - DC Components\n";
	cout << " 5 - First 9 frequency Components\n";
	cout << " 6 - IDCT\n";
	cout << " 7 - ROI\n";
	cout << " 8 - EXIT\n";	
        cout << "************************************************************************************************\n";
	cout << " ENTER YOUR CHOICE AND PRESS RETURN: ";

 cin >> choice;
 
 switch(choice)
 {
 case 1:
     {
 	image_name1 = "basel3.bmp";
        BGR = imread(image_name1, CV_LOAD_IMAGE_COLOR);
        if(!BGR.data) 
 	{
    		cout << "ERROR: COULD NOT LOAD IMAGE!" << endl;
    		return -1;
        }  
     
        imshow("f1", BGR);
        waitKey(0);
        
        cvDestroyAllWindows();
 	 	
     }
 break;

 case 2:
     {
 	cout << "\n\nCONVERTING RGB TO HSI VALUES..\n\n";
	hsi1 = HSI(BGR);
	imshow("I", hsi1);
        waitKey(0);
        
        cvDestroyAllWindows();

     }
 break;

 case 3:
     {
 	cout << "\n\n8x8 DCT..\n\n";
	dct1 = DCT(hsi1);
	imshow("F", dct1);
        waitKey(0);

        cvDestroyAllWindows();
	
     }
 break;

 case 4:
     {
 	cout << "\n\nDC Components..\n\n";
	dc1 = DCT_DC(dct1);
	imshow("D1", dc1);
        waitKey(0);
        
        cvDestroyAllWindows();
	
     }
 break;

case 5:

    {
 	cout << "\n\nFirst 9 freq Components..\n\n";
	dc9 = DCT_9(dct1);
	imshow("D2", dc9);
        waitKey(0);
        
        cvDestroyAllWindows();
     }
 break;

case 6:
     {
	

	idct1 = IDCT(dc1);
	imshow("R1", idct1);
        waitKey(0);
        
        //cvDestroyAllWindows();

	idct2 = IDCT(dc9);
	imshow("R2", idct2);
        waitKey(0);
	
        
        cvDestroyAllWindows();

     }
 break;

 case 7:
     {
 	image_name1 = "Building1.bmp";
	image_name2 = "Disk.bmp";
        Mat roi1 = imread(image_name1, CV_LOAD_IMAGE_COLOR);
	Mat roi2 = imread(image_name2, CV_LOAD_IMAGE_COLOR);

        if(!roi1.data || !roi2.data) 
 	{
    		cout << "ERROR: COULD NOT LOAD IMAGE!" << endl;
    		return -1;
        }  
	
	Mat hsi2 = HSI(roi1);
	sobel(hsi2,"ROI-Building1.bmp");
	Mat hsi3 = HSI(roi2);
	sobel(hsi3,"ROI-Disk.bmp");
     		
     }
 break;

 case 8:
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
