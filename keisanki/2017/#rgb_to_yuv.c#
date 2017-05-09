#include <cv.h>
#include <highgui.h>

int
main (int argc, char **argv)
{
  int x, y;
  uchar p[3];
  IplImage *img;

  if (argc != 2 || (img = cvLoadImage (argv[1], CV_LOAD_IMAGE_COLOR)) == 0)
    return -1;

  // (1)画素値（R,G,B）を順次取得し，変更する
  for (y = 0; y < img->height; y++) {
    for (x = 0; x < img->width; x++) {
      /* 画素値を直接グレーに変更する */
      p[0] = img->imageData[img->widthStep * y + x * 3];        // B
      p[1] = img->imageData[img->widthStep * y + x * 3 + 1];    // G
      p[2] = img->imageData[img->widthStep * y + x * 3 + 2];    // R
      int max = p[0];
      int min = p[0];
      int i;
      for (i=0;i<3;i++){
	if (max < p[i]){
	  max = p[i];
	}
	if (min > p[i]){
	  min = p[i];
	}
      }
      float gscale = (min + max) / 2;
      if (gscale < 90) {
        img->imageData[img->widthStep * y + x * 3] = cvRound (0);
        img->imageData[img->widthStep * y + x * 3 + 1] = cvRound (0);
        img->imageData[img->widthStep * y + x * 3 + 2] = cvRound (0);
      } else {
	img->imageData[img->widthStep * y + x * 3] = cvRound (255);
	img->imageData[img->widthStep * y + x * 3 + 1] = cvRound (255);
	img->imageData[img->widthStep * y + x * 3 + 2] = cvRound (255);
      }
    }
  }

  cvNamedWindow ("Image", CV_WINDOW_AUTOSIZE);
  cvShowImage ("Image", img);
  cvWaitKey (0);

  cvDestroyWindow ("Image");
  cvReleaseImage (&img);

  return 0;
}
