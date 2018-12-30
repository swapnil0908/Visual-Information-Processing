#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>
#include <math.h>

 using namespace cv;
 using namespace std;

int vis[1000][1000];
int pixelCount;
Mat I, I1, I2, F, L, M, erosion, dilation, erosion1, erosion2, erosion3, dilation1, dilation2, dilation3, dilation4, dilation5, dilation6, dilation7;

typedef struct info_shape
  {
	  int x;
	  int y;
	  int p;
  }info;

info shape[20], temp[20];

void clear(Mat img){

   for (int i = 0; i < img.rows; ++i)
   {
   	for (int j = 0; j < img.cols; ++j)
	{
		img.at<uchar>(i, j) = 0;
	}
    }
}

int min(int list[]) {
	int min = 255;
	for (int i = 0; i < sizeof(list); i++) {
		if (list[i] < min) {
			min = list[i];
		}
	}
	return min;
}

int max(int list[]) {
	int max = 0;
	for (int i = 0; i < sizeof(list); i++) {
		if (list[i] > max) {
			max = list[i];
		}
	}
	return max;
}

Mat binaryImage(Mat img, int threshold)
{
	for (int i = 0; i < img.rows; i++)
	{
		for (int j = 0; j < img.cols; j++)
		{
			if (int(img.at<uchar>(i, j)) <= threshold)
			{
				img.at<uchar>(i, j) = 0;//(black)If pixel intensity is greater than threshold
			}
			else
			{
				img.at<uchar>(i, j) = 255;//(white) If pixel intensity is less than threshold
			}
		}
	}

	return img;
}

bool check(Mat img, int i,int j){
  return (0<=i && i<img.rows && 0<=j && j<img.cols);
}

//run dfs using 4 connected component algorithm to find the pixel count for each shape
void DFS(Mat img, int i, int j)
{ 
	pixelCount++;                 
	  vis[i][j]=1;                


	if(check(img, i+1,j) && !vis[i+1][j] && img.at<uchar>(i+1, j) == 255)
	      DFS(img,i+1,j);

	if(check(img, i,j+1) && !vis[i][j+1] && img.at<uchar>(i, j+1) == 255)
	      DFS(img,i,j+1);
	
	if(check(img, i-1,j) && !vis[i-1][j] && img.at<uchar>(i-1, j) == 255)
	      DFS(img,i-1,j);
	
	if(check(img, i,j-1) && !vis[i][j-1] && img.at<uchar>(i, j-1) == 255)
	      DFS(img,i,j-1);
	
	
	
}

void clearVisited(Mat img){

   for (int i = 0; i < img.rows; ++i)
   {
   	for (int j = 0; j < img.cols; ++j)
	{
		vis[i][j] = 0;
	}
    }
}


int regions(Mat img)
{
    clearVisited(img);
    
   
    int numOfComponents=0;
    int b = 0;
    for (int i = 0; i < img.rows; ++i)
        for (int j = 0; j < img.cols; ++j)
            if (!vis[i][j] && img.at<uchar>(i, j) == 255)
            {    
		pixelCount=0;                  
                DFS(img, i, j);
		shape[b].x = i;
		shape[b].y = j;
		shape[b].p = pixelCount;
		if (pixelCount > 41)
		cout << "pixelCount: " << pixelCount << endl;
               	if(pixelCount>41)numOfComponents++;              
            }
 
    return numOfComponents;
}

Mat Erode(Mat img1){
	Mat img2 = img1.clone();
	clear(img2);
	int temp = 0;
	for (int i=0; i<img1.rows; i++){
	    for (int j=0; j<img1.cols; j++) {
	      if (img1.at<uchar>(i,j)==255) { 
		temp=0;
		for (int m=0; m<3; m++){
		  for (int n=0; n<3; n++) {
		    if ((i-2+m) >= 0 && (j-2+n) >=0 && (i-2+m) < img1.rows && (j-2+n) < img1.cols && img1.at<uchar>(i-2+m,j-2+n)==255){
		        temp++;
		    }
		  }
		}
		if (temp == 9){
		  img2.at<uchar>(i,j) = 255;
		}
		
	      }
	    }
	  }
	
	return img2;


}

Mat Dilate(Mat img1){
	Mat img2 = img1.clone();
	clear(img2);
	for (int i=0; i<img1.rows; i++){
	    for (int j=0; j<img1.cols; j++) {
	      if (img1.at<uchar>(i,j)==255) {       
		for (int m=0; m<3; m++){
		  for (int n=0; n<3; n++) {
		    if ((i-2+m) >= 0 && (j-2+n) >=0 && (i-2+m) < img1.rows && (j-2+n) < img1.cols && img1.at<uchar>(i-2+m, j-2+n)!=255){
		        img1.at<uchar>(i-2+m, j-2+n) = 255;
		     }
		  }
		}
	      }


	    }
	  }


	 for(int a=0; a < img1.rows;a++){
	 	for( int b=0 ;b < img1.cols; b++){
		    if((img1.at<uchar>(a,b))==255){
		      img2.at<uchar>(a,b)=F.at<uchar>(a,b);
		    }
		}
	    }

	
		return img2;


}


Mat Erosion_Gray(Mat img1) {
	int p[3][3];
	for (int x = 0; x < 3; x++) {
		for (int y = 0; y < 3; y++) {
			p[x][y] = 1;
		}
	}
	int list[10];
	Mat img2 = img1.clone();
	clear(img2);
	for (int i = 1; i < img1.rows - 1; i++) {
		for (int j = 1; j < img1.cols - 1; j++) {
			int  n = 0;
			for (int x = -1; x <= 1; x++) {
				for (int y = -1; y <= 1; y++) {
					list[n] = img1.at<uchar>(i + x, j + y)*p[x + 1][y + 1];
					n++;
				}
			}

			img2.at<uchar>(i, j) = min(list);
		}
	}
	
	return img2;

}

Mat Dilation_Gray(Mat img1) {

	Mat img2 = img1.clone();
	clear(img2);

	int p[3][3];
	for (int x = 0; x < 3; x++) {
		for (int y = 0; y < 3; y++) {
			p[x][y] = 1;
		}
	}
	int list[10];
	
	for (int i = 1; i < img1.rows - 2; i++) {
		for (int j = 1; j < img1.cols - 2; j++) {
			int  n = 0;
			for (int x = -1; x <= 1; x++) {
				for (int y = -1; y <= 1; y++) {
					list[n] = img1.at<uchar>(i + x, j + y)*p[x + 1][y + 1];
					n++;
				}
			}
			img2.at<uchar>(i, j) = max(list);
		}
	}
	
	return img2;
}

void Opening(Mat img){

	Mat img1 = Erosion_Gray(img);
	Mat img2 = Dilation_Gray(img1);
	
	imshow("Grayscale Opening", img2);
	waitKey(0);
        
        cvDestroyAllWindows();
}

void Closing(Mat img){

	
	Mat img1 = Dilation_Gray(img);
	Mat img2 = Erosion_Gray(img1);
	
	imshow("Grayscale Closing", img2);
	waitKey(0);
        
        cvDestroyAllWindows();
}

int main(int argc, char **argv) {  
  
  
  string image_name1;
  int choice;
  bool menu = true;
  while (menu != false) {
	cout << "\n\n************************************************************************************************\n";
	cout << " 1 - LOAD THE IMAGE I (TestImage-even-width.bmp) and convert to binary image and display.\n";
	cout << " 2 - BINARY EROSION/DILATION\n";
	cout << " 3 - GRAYSCALE EROSION/DILATION\n";
	cout << " 4 - NUMBER OF COMPONENTS\n";
	cout << " 8 - EXIT\n";	
        cout << "************************************************************************************************\n";
	cout << " ENTER YOUR CHOICE AND PRESS RETURN: ";

 cin >> choice;
 
 switch(choice)
 {
 case 1:
     {
 	image_name1 = "TestImage-even-width.bmp";
        I = imread(image_name1, CV_LOAD_IMAGE_COLOR);
        if(!I.data) 
 	{
    		cout << "ERROR: COULD NOT LOAD IMAGE!" << endl;
    		return -1;
        }  
     
        imshow("I", I);
        waitKey(0);
        
        cvDestroyAllWindows();
	
	I1 = imread(image_name1, CV_LOAD_IMAGE_GRAYSCALE);
	I2 = imread(image_name1, CV_LOAD_IMAGE_GRAYSCALE);
	L = imread(image_name1, CV_LOAD_IMAGE_GRAYSCALE);
	M = imread(image_name1, CV_LOAD_IMAGE_GRAYSCALE);
	
	int sum_intensity = 0;
	
	for (int i = 0; i < I.rows; i++)
	{
		for (int j = 0; j < I.cols; j++)
		{
			sum_intensity = sum_intensity + I.at<uchar>(i, j);	
		}
	}
 
	int threshold = sum_intensity/(I.rows*I.cols);
	threshold = 200;
	F = binaryImage(I1, threshold);	
	imshow("F", F);
        waitKey(0);
        
        cvDestroyAllWindows();
     }

 break;
case 2:
     {

	erosion = Erode(F);
        
	dilation3 = Dilate(erosion);
	
	erosion1 = Erode(dilation3);
	
	erosion2 = Erode(erosion1);
	
	dilation4 = Dilate(erosion2);
	
	dilation5 = Dilate(dilation4);

	dilation6 = Dilate(dilation5);

	erosion3 = Erode(dilation6);
	
	dilation7 = Dilate(erosion3);
	imshow("Binary Image after Morphological Operations", dilation7);
        waitKey(0);
        
        cvDestroyAllWindows();
	
     }
 break;

case 3:
     {
	
	Mat IMG = Erosion_Gray(I2);
	//namedWindow("Gray Scale Eroded Image", CV_WINDOW_AUTOSIZE);
	imshow("Gray Scale Eroded Image", IMG);
	waitKey(0);
        
        cvDestroyAllWindows();

	Mat IMG1 = Dilation_Gray(I2);
	//namedWindow("Gray Scale Dilated Image", CV_WINDOW_AUTOSIZE);
	imshow("Gray Scale Dilated Image", IMG1);
	waitKey(0);
        
        cvDestroyAllWindows();
	
	Opening(I2);
	
	Closing(I2);
	
     }
 break;

case 4 :
     {
	for(int a=0;a<20;a++)
	{
		shape[a].x = 0;
		shape[a].y = 0;		
		shape[a].p = 0;
	}
	int components = regions(dilation7);
	cout << "TOTAL CONNECTED COMPONENTS IN THE IMAGE: " << components <<endl;
	
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
