#include <cv.h>
#include <highgui.h>
#include <math.h>
#include <stdio.h>
#define THRESHOLD 200

float calcY(int x, int y, IplImage *img) {
  int p[3];

  p[0] = img->imageData[img->widthStep * y + x * 3];        // B
  p[1] = img->imageData[img->widthStep * y + x * 3 + 1];    // G
  p[2] = img->imageData[img->widthStep * y + x * 3 + 2];    // R

  float Y;
  Y = 0.299 * p[2] + 0.587 * p[1] + 0.114 * p[0];

  return Y;
}

float calcG(int x, int y, IplImage *img) {
  int i, j;
  float sum_x = 0;
  float sum_y = 0;
  float G;
  for (i = -1; i <= 1; i++) {
    for (j = -1; j <= 1; j++) {
      sum_x += i * calcY(x+i, y+j, img);
      sum_y += j * calcY(x+i, y+j, img);
    }
  }
  G = sqrt(sum_x * sum_x + sum_y * sum_y);
  return G;
}

int
main (int argc, char **argv)
{
  IplImage *src_img;

  // (1)画像の読み込み
  if (argc != 2 || (src_img = cvLoadImage (argv[1], CV_LOAD_IMAGE_COLOR)) == 0)
    return -1;

  // tmp_img = cvCreateImage (cvGetSize (src_img), IPL_DEPTH_16S, 1);

  // (2)画素値（R,G,B）を順次取得し, 処理を加える
  int x, y;
  for (y = 1; y < src_img->height - 1; y++) {
    for (x = 1; x < src_img->width - 1; x++) {
      float gray = calcY(x,y, src_img);
      float pix = calcG(x,y, src_img);

      if (pix > THRESHOLD) {
        src_img->imageData[src_img->widthStep * y + x * 3] = cvRound (255);
        src_img->imageData[src_img->widthStep * y + x * 3 + 1] = cvRound (255);
        src_img->imageData[src_img->widthStep * y + x * 3 + 2] = cvRound (255);
      } else {
        src_img->imageData[src_img->widthStep * y + x * 3] = cvRound (0);
        src_img->imageData[src_img->widthStep * y + x * 3 + 1] = cvRound (0);
        src_img->imageData[src_img->widthStep * y + x * 3 + 2] = cvRound (0);
      }
    }
  }



  // (5)画像の表示
  cvNamedWindow ("Detection", CV_WINDOW_AUTOSIZE);
  cvShowImage ("Detection", src_img);
  cvWaitKey (0);

  cvDestroyWindow ("Detection");
  cvReleaseImage (&src_img);
  // cvReleaseImage (&tmp_img);


  return 0;
}
