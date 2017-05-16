#include <cv.h>
#include <highgui.h>
#include <stdio.h>
#include <math.h>
#define GREEN_Y 140
#define GREEN_U -85
#define GREEN_V -100

void convert(int *p, float *yuv);

int isGreen(float *yuv);

int
main (int argc, char **argv)
{
  int x, y;
  int p[3];
  IplImage *img;

  if (argc != 2 || (img = cvLoadImage (argv[1], CV_LOAD_IMAGE_COLOR)) == 0)
    return -1;

  // (1)画素値（R,G,B）を順次取得し，YUVに変換する
  for (y = 0; y < img->height; y++) {
    for (x = 0; x < img->width; x++) {
      float yuv[3];

      /* 画素値を直接グレーに変更する */
      p[0] = img->imageData[img->widthStep * y + x * 3];        // B
      p[1] = img->imageData[img->widthStep * y + x * 3 + 1];    // G
      p[2] = img->imageData[img->widthStep * y + x * 3 + 2];    // R
      convert(p, yuv);

      if (isGreen(yuv)) {
        img->imageData[img->widthStep * y + x * 3] = cvRound (p[0]);      // B
        img->imageData[img->widthStep * y + x * 3 + 1] = cvRound (p[1]);  // G
        img->imageData[img->widthStep * y + x * 3 + 2] = cvRound (p[2]);  // R
      } else {
        img->imageData[img->widthStep * y + x * 3] = cvRound (0);      // B
        img->imageData[img->widthStep * y + x * 3 + 1] = cvRound (0);  // G
        img->imageData[img->widthStep * y + x * 3 + 2] = cvRound (0);  // R
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

void convert(int *p, float *array) {
  float Y, U, V;
  Y = 0.299 * p[2] + 0.587 * p[1] + 0.114 * p[0];
  U = -0.168736 * p[2] -0.331264 * p[1] + 0.5 * p[0];
  V = 0.5 * p[2] - 0.418688 * p[1] - 0.081312 * p[0];

  array[0] = Y;
  array[1] = U;
  array[2] = V;
}

int isGreen(float *yuv) {
  int green = 0;
  float r;

  r = sqrt((yuv[0] - GREEN_Y) * (yuv[0] - GREEN_Y) + (yuv[1] - GREEN_U) * (yuv[1] - GREEN_U) + (yuv[2] - GREEN_V) * (yuv[2] - GREEN_V));
  if (r <= 220 && r >= 200) {
    green = 1;
  }

  printf("%lf\n", r);

  if (green == 1) {
    return 1;
  } else {
    return 0;
  }
}
