import gab.opencv.*;
import java.awt.Rectangle;
import processing.serial.*;
import processing.video.*;

OpenCV opencv;

Serial CreoqodeNova_Port;

Rectangle[] faces;

Capture video;

int avgX;
int avgY;
void setup() {
  size(320, 240);
  video = new Capture(this, 320, 240);
  opencv = new OpenCV(this, 320, 240);
  opencv.loadCascade(OpenCV.CASCADE_FRONTALFACE); 

  video.start();

  CreoqodeNova_Port = new Serial(this, "COM4", 9600);
  CreoqodeNova_Port.bufferUntil('\n');

  faces = opencv.detect();
}
