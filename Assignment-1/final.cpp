#include <opencv2/opencv.hpp>
#include <iostream>

  using namespace cv;
  using namespace std;
  int i,j, histogram_original[256], histogram_modified[256]; // number of pixels for each pixel value.
  int  cml[256];
  int components;
  int vis[1000][1000];
  int pixelCount;
  int sum_intensity;
  int color;
  Mat img1, enhanced_image;
  typedef struct info_shape
  {
	  int x;
	  int y;
	  int p;
  }info;

  info shape[20], temp[20];


//************************ NEGATIVE IMAGE ************************************************
  void negativeImage(Mat original_image, Mat modified_image){
    	for (i = 0; i < original_image.rows; i++)					
	{
	   for (j = 0; j < original_image.cols; j++)
	    {
//substract each pixel(unsigned char type) at ith row and jth column from 255.
	     modified_image.at<uchar>(i, j) = 255 - original_image.at<uchar>(i,j);					  
	    }
	}
//Dsiplay Negative image.
  	imshow("NEGATIVE IMAGE", modified_image);
  	waitKey(0);
  } 
//*************************GENERATE HISTOGRAM**********************************************
   void generateHistogram(Mat original_image, Mat modified_image){
// Calculate number of pixels for each intensity value
	for (i = 0; i < original_image.rows; i++)					
	{
 		for (j = 0; j < original_image.cols; j++)
		{
			histogram_modified[(int)modified_image.at<uchar>(i,j)]++;
                        histogram_original[(int)original_image.at<uchar>(i,j)]++;
                }
   	}  
  }

//**************************DISPLAY IMAGE HISTOGRAM*****************************************
   void displayHistogram(int histogram[], string window_name){
//draw the histograms
	int histogram_height = 400;
	int histogram_width = 512;
	//int maxintensity = 0;
	int binary_width = cvRound((double)histogram_width / 256);
	Mat histogram_image(histogram_height, histogram_width, CV_8UC1, Scalar(255, 255, 255));

//find maximum intensity element from histogram      
       int maxintensity = histogram[0];

        for (int i = 1; i < 256; i++)
	{
		if (histogram[i] > maxintensity)
		{
			maxintensity = histogram[i];
		}
	}
// normalise the histogram values between 0 and histogram_image.rows;
        for (int i = 0; i < 256; i++)
	{
		histogram[i] = ((double)histogram[i] / maxintensity) * histogram_image.rows;
	}
// draw the intensity line for histogram
        for (int i = 0; i < 256; i++)
	{
   line(histogram_image, Point(binary_width*(i), histogram_height), Point(binary_width*(i), histogram_height - histogram[i]), Scalar(0,0,0),1,8,0);
  	}
// display histogram 
 	  //namedWindow(window_name, CV_WINDOW_AUTOSIZE);
     	  imshow(window_name, histogram_image);
          waitKey(0);
  
  }


//***************EQUALIZE HISTOGRAM OF ORIGINAL IMAGE**************************************

 void Equalize(Mat img){
	// calculate the size of image
	int pixels = img.rows*img.cols;
	
	// calculate the probabilty for each intensity
	float probability[256];
	for (int i = 0; i < 256; i++)
	{
		probability[i] = (double)histogram_original[i] / pixels;
	}
	
	// generate cumulative frequency histogram
	cml[0] = histogram_original[0];
	for (int i = 1; i < 256; i++)
	{
		cml[i] = histogram_original[i] + cml[i - 1];
	}

	//scale the histogram
	int scaled[256];

	for (int i = 0; i < 256; i++)
	{
		scaled[i] = cvRound((double)cml[i] * (float)(255.0/pixels));
	}

	//generate equalized histogram
	float equalized_histogram[256] = {0};

	for (int i = 0; i < 256; i++)
	{
		equalized_histogram[scaled[i]] = equalized_histogram[scaled[i]] + probability[i];
	}
	int final_hist[256];
	for (int i = 0; i < 256; i++)
	{
		final_hist[i] = cvRound(equalized_histogram[i] * 255);
	}

	//generate equalized image
	enhanced_image = img.clone();
	for (int i = 0; i < img.rows; i++)
	{
		for (int j = 0; j < img.cols; j++)
		{
			enhanced_image.at<uchar>(i, j) = saturate_cast<uchar>(scaled[img.at<uchar>(i, j)]);
		}
	}
	
	displayHistogram(final_hist, "EQUALIZED HISTOGRAM");
	imshow("ENHANCED IMAGE", enhanced_image);
	waitKey(0);
		
}


//***********************************************CLEAR HISTOGRAM************************

void initialize_intensity(){

// initialize all intensity values to 0.	
  for(i=0;i<256;i++)
  {
	histogram_original[i] = 0;
    	histogram_modified[i] = 0;
  }

}


//***********************************************BINARY IMAGE**************************

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

//*******************************************LABEL IMAGE***************************************

//chek if the pixel is in bounds of the image
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
    //clear visited array
    clearVisited(img);
    
   
     int numOfComponents=0;
     int b = 0;
    for (int i = 0; i < img.rows; ++i)
        for (int j = 0; j < img.cols; ++j)
            if (!vis[i][j] && img.at<uchar>(i, j) == 255)
            {    
		pixelCount=0;                  
                DFS(img, i, j);
		//store the pixelcount and starting i,j values for each shape in struct shape
		shape[b].x = i;
		shape[b].y = j;
		shape[b].p = pixelCount;
		b++;  
               if(pixelCount>1)numOfComponents++;              
            }
 
    return numOfComponents;
}

int findmax(){
	//find the shape with maximum number of pixels and store in the first array location
	int Max = shape[0].p;
	
	for(int i=0;i<components;i++){
		if(shape[i].p > Max)
			Max = shape[i].p;
	}

return Max;

}

int findmin(){
	//find the shape with minimum number of pixels and store in the second array location
	int Min = shape[0].p;
	
	for(int i=0;i<components;i++){
		if(shape[i].p < Min && shape[i].p > 1)
			Min = shape[i].p;
	}

return Min;

}

//run DFS again with 4 connected components algorithm to label the shapes with largest, smallest and medium pixelcount with specified colors
void DFS_1(Mat img, int i, int j, int color)
{ 
	  vis[i][j]=1;

	  img.at<uchar>(i, j) = color;
		
	if(check(img, i+1,j) && !vis[i+1][j] && img.at<uchar>(i+1, j) == 255)
	      DFS_1(img,i+1,j,color);
	
	if(check(img, i,j+1) && !vis[i][j+1] && img.at<uchar>(i, j+1) == 255)
	      DFS_1(img,i,j+1,color);
	
	if(check(img, i-1,j) && !vis[i-1][j] && img.at<uchar>(i-1, j) == 255)
	      DFS_1(img,i-1,j,color);
	
	if(check(img, i,j-1) && !vis[i][j-1] && img.at<uchar>(i, j-1) == 255)
	      DFS_1(img,i,j-1,color);
	
}

//label the shapes according to the repective pixel count
Mat colorShapes(Mat img, info temp[20]) 
{
     clearVisited(img);
   
    int b = 0;
    for (int i = 0; i < img.rows; ++i)
        for (int j = 0; j < img.cols; ++j)
            if (!vis[i][j] && img.at<uchar>(i, j) == 255)
            {    
		if(i == temp[0].x && j == temp[0].y)
			color = 200;
		else if(i == temp[1].x && j == temp[1].y)
			color = 60;
		else
			color = 120;

               	DFS_1(img, i, j, color);
            }
	

	return img;

}

//**********************************************************************************************************

int main(int argc, char **argv) {  
 
  string image_name;
  Mat original_image, modified_image, img;
  int choice;
  bool menu = true;
  while (menu != false) {
	cout << "\n\n************************************************************************************************\n";
	cout << " 1 - LOAD AND DISPLAY THE ORIGINAL IMAGE AND ITS HISTOGRAM.\n";
	cout << " 2 - DISPLAY THE NEGATIVE OF THE ORIGINAL IMAGE WITH ITS MODIFIED HISTOGRAM\n";
	cout << " 3 - DISPLAY THE ENHANCED IMAGE AND ITS EQUALIZED HISTOGRAM\n";
	cout << " 4 - CALCULATE THE OPTIMAL THRESHOLD VALUE, DISPLAY THE BINARY IMAGE AND THE LABELED IMAGE\n";
	cout << " 5 - EXIT\n";
        cout << "************************************************************************************************\n";
	cout << " ENTER YOUR CHOICE AND PRESS RETURN: ";

 cin >> choice;
 
 switch(choice)
 {
 case 1:
     {
 	cout << "ENTER THE IMAGE NAME..\n";
 	cin >> image_name;
 	cout << "LOADING IMAGE....\n\n";
        original_image = imread(image_name, CV_LOAD_IMAGE_GRAYSCALE);
	img = original_image;
        modified_image = imread(image_name, CV_LOAD_IMAGE_GRAYSCALE);
        if(!original_image.data || !modified_image.data) 
 	{
    		cout << "ERROR: COULD NOT LOAD IMAGE." << endl;
    		return -1;
        }  
     
        imshow("ORIGINAL IMAGE", original_image);
        waitKey(0);
        initialize_intensity();
        generateHistogram(original_image,modified_image);
        displayHistogram(histogram_original, "ORIGINAL IMAGE HISTOGRAM");
        cvDestroyAllWindows();
 	 	
     }
 break;
 
  
 case 2:
     {
 	cout << "CREATING NEGATIVE IMAGE AND GENERATING MODIFIED HISTOGRAM....\n\n";
        for(i=0;i<256;i++){
	histogram_original[i] = 0;
    	histogram_modified[i] = 0;
  	}
  	negativeImage(original_image,modified_image);
        initialize_intensity();
        generateHistogram(original_image,modified_image);
	displayHistogram(histogram_modified, "NEGATIVE IMAGE HISTOGRAM");
        cvDestroyAllWindows();
     }
 break;
 
case 3:
     {
 	cout << "\n\nGENERATING ENHANCED IMAGE AND EQUALIZED HISTOGRAM..\n";
        initialize_intensity();
        generateHistogram(img,modified_image);
 	Equalize(img);
	waitKey(0);
        cvDestroyAllWindows();
     }
 break;

 case 4:
     {
 	
        cout << "\n\nCALCULATING OPTIMAL THRESHOLD, GENERATING BINARY IMAGE AND LABELING IMAGE..\n";
  	initialize_intensity();
   	int sum_intensity = 0;
  	for (int i = 0; i < img.rows; i++)
	{
		for (int j = 0; j < img.cols; j++)
		{
			sum_intensity = sum_intensity + img.at<uchar>(i, j);	
		}
	}
 
	int threshold = sum_intensity/(img.rows*img.cols);
	img = binaryImage(img, threshold);
	cout << "OPTIMAL THRESHOLD VALUE T: " << threshold << endl;
	imshow("BINARY IMAGE", img);
	waitKey(0);
	
	for(int a=0;a<20;a++)
	{
		shape[a].x = 0;
		shape[a].y = 0;
		shape[a].p = 0;
	}

	components = regions(img);
	cout << "TOTAL CONNECTED COMPONENTS IN THE IMAGE: " << components <<endl;
	int max = findmax();
	int min = findmin();
	
	int b = 2;
	for(int a=0;a<components;a++)
	{
		if(shape[a].p == max)
			temp[0] = shape[a];
		if(shape[a].p == min)
			temp[1] = shape[a];
		if(shape[a].p != min && shape[a].p != max)
		{
			temp[b] = shape[a];
			b++;
		}
	}	

	img1 = colorShapes(img, temp);
        imshow("LABELED IMAGE", img1);
	waitKey(0);
	
	cvDestroyAllWindows();
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
