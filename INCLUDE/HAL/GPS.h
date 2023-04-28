

#define PI  3.14159265358979323846



float GPS_converToDeg (float angle); //1

float GPS_convertToRad(float degValue); //2

void GPS_read ();  //3

void GPS_format(); //4

float GPS_getDistance(float currentLong,float currentLat,float destinationLong,float destinationLat); //5



/*Note;

the correct sequence to get your current distance from GPS module 1 ==> 2 ==>3 ==>4 ==>5

but destination location you will pass it 
*/