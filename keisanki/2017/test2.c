#include <cv2.h>
#include <highgui.h>
#include <stdio.h>

/* グローバル変数 */
CvFont font;
IplImage *img = 0;
int xx,yy,i=0;
int bevent=0;

IplImage *draw_img = 0;

/* プロトタイプ宣言 */
void on_mouse (int event, int x, int y, int flags);

/* メイン関数 */
int
main (int argc, char *argv[])
{
  int c;
  CvCapture *capture = 0;
  // 指定された番号のカメラに対するキャプチャ構造体を作成する
  capture = cvCreateCameraCapture(0);

  // 画像領域を確保し，初期化する
  img = cvQueryFrame (capture);
  cvInitFont (&font,CV_FONT_HERSHEY_SCRIPT_SIMPLEX , 2.0, 2.0, 0.0, 5);
  
  // ウィンドウを作成し，マウスイベントに対するコールバック関数を登録する
  cvNamedWindow ("Image", CV_WINDOW_AUTOSIZE);
  cvSetMouseCallback ("Image", on_mouse, 0);
  cvShowImage ("Image", img);

  // 'Esc'キーが押された場合に終了する
  while (1) {
    img = cvQueryFrame (capture);
    draw_img=cvCloneImage(img);

    cvShowImage ("Image", img);
    c = cvWaitKey (0);
    if (c == '\x1b')
      return 1;
  }

  cvDestroyWindow ("Image");
  cvReleaseImage (&img);

  return 0;
}

/* コールバック関数 */
void
on_mouse (int event, int x, int y, int flags)
{
  char str[64];
  static int line = 0;
  const int max_line = 15, w = 15, h = 30;
  
  // マウスイベントを取得
  switch (event) {
    
    case CV_EVENT_MOUSEMOVE:   /* マウスを動かしたときに左クリックした後なら線を描く */
      if(bevent==CV_EVENT_LBUTTONDOWN){
        cvLine(img, cvPoint(x,y), cvPoint(xx,yy), CV_RGB (255, 255, 0),10, 8, 0 );
        xx=x;
        yy=y;
        i++;
      }
      break;
   
    case CV_EVENT_LBUTTONDOWN:  /* 左クリックしたら線の描画が始まる */
      xx=x;
      yy=y;
      bevent=CV_EVENT_LBUTTONDOWN;
      break;
    
    case CV_EVENT_RBUTTONDOWN:  /* 右クリックしたら円の描画が始まる */
      xx=x;
      yy=y;
      bevent=CV_EVENT_RBUTTONDOWN;
      break;
    
    case CV_EVENT_LBUTTONUP: /* 線の描画 */
      if(bevent==CV_EVENT_LBUTTONDOWN){
        cvLine(img, cvPoint(x,y), cvPoint(xx,yy), CV_RGB (255, 255, 0),10, 8, 0 );
      }
      bevent=CV_EVENT_LBUTTONUP;    
      break;
      
    case CV_EVENT_RBUTTONUP: /* 右クリックした点から離した点までの距離を半径とする円を描く */
      if(bevent=CV_EVENT_RBUTTONDOWN){
        cvCircle(img, cvPoint(xx,yy),cvSqrt((xx-x)*(xx-x)+(yy-y)*(yy-y)),CV_RGB (0, 255, 255),10, 8, 0 );
      }
      break;
      
    case CV_EVENT_LBUTTONDBLCLK: /*  左をダブルクリックすると画面がリセットする */
      cvZero (img);
      break;
      
    case CV_EVENT_RBUTTONDBLCLK: /* 右をダブルクリックするとHELLOの文字がスタンプされる */
      snprintf (str, 64, "%s", "Hello!");    
      cvPutText (img, str, cvPoint (x,y), &font, CV_RGB (255, 255, 0));
      break;

  }

  
  // マウス座標，イベント，修飾キーなどを画像に描画，表示
  cvShowImage ("Image", img);
}
