#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>
#include <math.h>
#define PI 3.14

 using namespace cv;
 using namespace std;
  
Mat img1, img2, img3, img4, img5, img6, img7, img8;

void clear(Mat img){
	for(int i=0;i<img.rows;i++)
		for(int j=0;j<img.cols;j++)
			img.at<uchar>(i,j)=0.0;
}

void unsharp(Mat image_original, Mat image_new, double gaussian[3][3]){
 
  double sum;

  for(int i=0;i<image_new.rows;i++)
        {
          for (int j=0;j<image_new.cols;j++)
          {
               sum=0;
		
              for (int r=-1;r<=1;r++)
               {
                    for (int c=-1;c<=1;c++)
                    {
		
			sum = sum + gaussian[r+1][c+1] *(double)image_original.at<uchar>(i-r,j-c); 	
		    }
		}

            image_new.at<uchar>(i,j)=saturate_cast<uchar>(sum);

          }
        }

}


void add_sub(Mat image_original, Mat image_new){

        for(int i=0;i<image_new.rows;i++)
        {
          for (int j=0;j<image_new.cols;j++)
          {
image_new.at<uchar>(i,j)=saturate_cast<uchar>( image_original.at<uchar>(i,j) + 1* (image_original.at<uchar>(i,j)-image_new.at<uchar>(i,j)));
          }
        }

}

int gradient_x(Mat image, int x, int y){

 return image.at<uchar>(y-1, x-1) + 2*image.at<uchar>(y, x-1) + image.at<uchar>(y+1, x-1) -
                  image.at<uchar>(y-1, x+1) - 2*image.at<uchar>(y, x+1) - image.at<uchar>(y+1, x+1);

}

int gradient_y(Mat image, int x, int y){

 return image.at<uchar>(y-1, x-1) + 2*image.at<uchar>(y-1, x) + image.at<uchar>(y-1, x+1) -
                  image.at<uchar>(y+1, x-1) - 2*image.at<uchar>(y+1, x) - image.at<uchar>(y+1, x+1);

}

void sobel(Mat img1, Mat img){
 
 for(int i = 1; i < img.rows - 1; i++){
            for(int j = 1; j < img.cols - 1; j++){
              int G_x = gradient_x(img, j,i);
              int G_y = gradient_y(img, j,i);
              int sum1 = abs(G_x) + abs(G_y);
                img1.at<uchar>(i,j) = saturate_cast<uchar>(sum1);
            }
        }

}

void LoG_filter(int n,double s, int image){

	int mask[n][n];
	int scale;
	double gaussian[3][3]={ {1,2,1},{2,4,2},{1,2,1} };
	//need to use scaling factor (calculated approximately) for the edges to be more clear
	if(n==7)
        	scale = 32500;
	if(n==11)
		scale = 40000;
	double s2 = pow(s,2);
	double s4 = pow(s,4);
	int min = -n/2;
	int max = n/2;
	double k = pow(1/(pow(2*M_PI,0.5)*s2),2);
		
	cout << endl;	
	cout << "n: " << n << endl;
	cout << "sigma: " << s << endl;
	cout << endl << "LoG MASK:" << endl;
	for(int i=min;i<=max;i++)
	{
		for(int j=min;j<=max;j++)
		{
			
			double temp = ((pow(i,2) + pow(j,2))/s2)-2;
			double temp1 = exp(-(pow(i,2) + pow(j,2)) / (2.0 * s2));
			double value = k*temp*temp1;
			if(n==7){
			mask[i+max][j+max] = (int)((value * scale));
			}

			if(n==11){
				if(3<=(i+max) && (i+max)<=8 && 3<=(j+max) && (j+max)<=8){
					mask[i+max][j+max] = (int)((value * scale));
				}
				else{
					mask[i+max][j+max] = (int)((value * scale * -1));
				}	
			}
			cout << mask[i+max][j+max] << "\t";
			

		}
		
		cout << endl;
	}


     if(image == 1){
	img7 = img1.clone();
	unsharp(img1,img7,gaussian);
	img8 = img7.clone();
	clear(img8);

	double sum;
	

  for(int i=0;i<img8.rows;i++)
        {
          for (int j=0;j<img8.cols;j++)
          {
               sum=0;
		
              for (int r=min;r<=max;r++)
               {
                    for (int c=min;c<=max;c++)
                    {
		
			sum = sum + mask[r+max][c+max] *(double)img1.at<uchar>(i-r,j-c); 	
		    }
		}

            img8.at<uchar>(i,j)=saturate_cast<uchar>(sum);

          }
        }
	
	if(n == 7)
		imshow("E1_1", img8);
	if(n == 11)
		imshow("E1_2", img8);
	waitKey(0);
 	cvDestroyAllWindows();
	
    }
	
     if(image == 2){
	img7 = img2.clone();
	unsharp(img2,img7,gaussian);
	img8 = img7.clone();
	clear(img8);

	double sum;
	

  for(int i=0;i<img8.rows;i++)
        {
          for (int j=0;j<img8.cols;j++)
          {
               sum=0;
		
              for (int r=min;r<=max;r++)
               {
                    for (int c=min;c<=max;c++)
                    {
		
			sum = sum + mask[r+max][c+max] *(double)img2.at<uchar>(i-r,j-c); 	
		    }
		}

            img8.at<uchar>(i,j)=saturate_cast<uchar>(sum);

          }
        }
	
	if(n == 7)
		imshow("E2_1", img8);
	if(n == 11)
		imshow("E2_2", img8);
	waitKey(0);
 	cvDestroyAllWindows();
	
    }
	
}


int main(int argc, char **argv) {  
 
  string image_name1, image_name2;
  int choice;
  double gaussian[3][3]={ {1,2,1},{2,4,2},{1,2,1} };
	for (int i=0;i<3;i++)
        	for (int j=0;j<3;j++)
        	    gaussian[i][j]= gaussian[i][j]/16;
  bool menu = true;
  while (menu != false) {
	cout << "\n\n************************************************************************************************\n";
	cout << " 1 - LOAD AND DISPLAY THE ORIGINAL IMAGES f1 AND f2.\n";
	cout << " 2 - UNSHARP MASKING\n";
	cout << " 3 - SOBEL OPERATOR\n";
	cout << " 4 - LoG MASK\n";
	cout << " 5 - EXIT\n";	
        cout << "************************************************************************************************\n";
	cout << " ENTER YOUR CHOICE AND PRESS RETURN: ";

 cin >> choice;
 
 switch(choice)
 {
 case 1:
     {
 	cout << "ENTER THE IMAGE NAME (f1)\n";
 	cin >> image_name1;
 	cout << "ENTER THE IMAGE2 NAME (f2)\n";
	cin >> image_name2;
        img1 = imread(image_name1, CV_LOAD_IMAGE_GRAYSCALE);
	img2 = imread(image_name2, CV_LOAD_IMAGE_GRAYSCALE);
        if(!img1.data || !img2.data) 
 	{
    		cout << "ERROR: COULD NOT LOAD IMAGE!" << endl;
    		return -1;
        }  
     
        imshow("f1", img1);
	imshow("f2", img2);
        waitKey(0);
        
        cvDestroyAllWindows();
 	 	
     }
 break;

 case 2:
     {
 	cout << "UNSHARP MASKING.....\n";
	img3 = img1.clone();
	img4 = img2.clone();
	//clear the image
	clear(img3);
	clear(img4);   	
	//blur the image by using gaussian filter
	unsharp(img1,img3,gaussian);
	//subtract blur image from original and add the output back to original image
	add_sub(img1,img3);
	unsharp(img2,img4,gaussian);
	add_sub(img2,img4);

	imshow("E1", img3);
	imshow("E2", img4);
        waitKey(0);
	
        cvDestroyAllWindows();
 	 	
     }
 break;

 case 3:
     {
 	cout << "\nSOBEL OPERATOR..\n\n";
	img3 = img1.clone();
	img4 = img2.clone();	
	clear(img3);
	clear(img4);
   	//blur the image before applying sobel filter
	unsharp(img1,img3,gaussian);
	unsharp(img2,img4,gaussian);		

	img5 = img3.clone();
	img6 = img4.clone();

	clear(img5);
	clear(img6);
	//apply sobel filters
	sobel(img5, img3);
	sobel(img6, img4);

	imshow("Es1", img5);
	imshow("Es2", img6);
	waitKey(0);
 	cvDestroyAllWindows();
     }
 break;
	
 case 4:
     {
 	cout << "\nLoG MASK..\n\n";
	LoG_filter(7,1.4,1);
	LoG_filter(11,5,1);

	LoG_filter(7,1.4,2);
	LoG_filter(11,5,2);
	
     }

 break;

 case 5:
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
