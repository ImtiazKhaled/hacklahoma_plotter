import geomerative.*;

RShape grp;
RPoint[][] pointPaths;

String fileName = "test"; // Name of the file you want to convert, as to be in the same directory
String penUp= "M03 S0 \n"; // Command to control the pen, it change beetween differents firmware
String penDown = "M03 S20 \n";// This settings was made for my custom CNC Drawing machine
Boolean SaveState=false;
float[] xcoord = { 0,25};// These variables define the minimum and maximum position of each axis for your output GCode 
float[] ycoord = { 0,25};// These settings also change between your configuration
String[] lines=null;
String[] temp=null;
ArrayList <Float> x= new ArrayList<Float>();
ArrayList <Boolean> ps= new ArrayList<Boolean>();
ArrayList <Float> y= new ArrayList<Float>();

String gcodecommand ="G0 F16000 \n G0"+ penUp; // String to store the Gcode we wil save later

float xmag, ymag, newYmag, newXmag = 0;
float z = 0;

boolean ignoringStyles = false;
int filesaved = 0;

void setup(){
  size(600, 600, P3D);
  // VERY IMPORTANT: Allways initialize the library before using it
  RG.init(this);
  RG.ignoreStyles(ignoringStyles);
  
  RG.setPolygonizer(RG.ADAPTATIVE);
  
  grp = RG.loadShape(fileName +".svg");
  grp.centerIn(g, 100, 1, 1);
  
  pointPaths = grp.getPointsInPaths();
  
  translate(width/2, height/2);
  
  newXmag = mouseX/float(width) * TWO_PI;
  newYmag = mouseY/float(height) * TWO_PI;
  
  float diff = xmag-newXmag;
  if (abs(diff) >  0.01) { xmag -= diff/4.0; }
  
  diff = ymag-newYmag;
  if (abs(diff) >  0.01) { ymag -= diff/4.0; }
  
  rotateX(-ymag); 
  rotateY(-xmag); 
  
  background(0);
  stroke(255);
  noFill();
  
 if( filesaved == 0){
  for(int i = 0; i<pointPaths.length; i++){
    if (pointPaths[i] != null) {
      beginShape();
      for(int j = 0; j<pointPaths[i].length; j++){
        vertex(pointPaths[i][j].x, pointPaths[i][j].y);
        
        float xmaped = map(pointPaths[i][j].x,-200, 200, xcoord[1], xcoord[0]);
        float ymaped = map(pointPaths[i][j].y,-200, 200, ycoord[0] , ycoord[1]);
        if(j == 1){
          gcodecommand = gcodecommand + penDown;
        }
        gcodecommand = gcodecommand + "G1 X"+ str(xmaped)+" Y"+str(ymaped) +"\n"; 
      }
      endShape();
    }
   gcodecommand = gcodecommand + penUp;
  
   if(i == pointPaths.length-1){
      String[] gcodecommandlist = split(gcodecommand, '\n');
      saveStrings(fileName+".txt", gcodecommandlist); 
      filesaved = 1;
      println("finished");
   }
  }
  
}
lines = loadStrings(fileName+".txt");
  //println(lines.length);
  for (int i=2; i<lines.length-1; i++) {
    temp=split(lines[i], ' ');
    if(temp[1].contains("S")){
    SaveState=true;
    ps.add(SaveState);
    println(temp[1]);
    x.add(0.0);
    y.add(0.0);
    }else{
    SaveState=false;
    ps.add(SaveState);
    println(temp[1]);
    x.add(float(temp[1].substring(1)));
    y.add(float(temp[2].substring(1))); 
    }
}

}

void draw(){  
}

void mousePressed(){
  ignoringStyles = !ignoringStyles;
  RG.ignoreStyles(ignoringStyles);
}
