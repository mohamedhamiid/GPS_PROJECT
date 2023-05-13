#define PI  3.14159265358979323846

double ToDegree(double value);

double GPS_convertToRad(double degValue); 

double GPS_getDistance(double currentLat,double currentLong,double previousLat,double previousLong);

void GPS_read ();  



//**************************   ToDegree *********************************************//
/* @breif It take the value which recived from GPS module (lat & long) and convert   */
/* this value to degree                                                              */
/* @parameters double value                                                          */
/* @return double                                                                    */
/*************************************************************************************/

//**************************   GPS_convertToRad *************************************//
/* @breif It take the deg value which recived from "ToDegree" function and convert   */
/* this value to Rad to substitute in Haversine equation                             */
/* @parameters double degvalue                                                       */
/* @return double                                                                    */
/*************************************************************************************/


//************************** GPS_getDistance ***********************************************//
// @breif  function to calculate distance between two points using data given from the GPS  */
// using Haversine formula                                                                  */
// Haversine formula: a = sin²(Δφ/2) + cos φ1 ⋅ cos φ2 ⋅ sin²(Δλ/2)                         */
//  c = 2 * atan2(sqrt(a), sqrt(1 - a))                                                     */
// distance = Earth radius *c                                                               */
// @parameters  double currentLat,double currentLong,double previousLat,double previousLong */  
// @return double                                                                           */
//******************************************************************************************//




/********************************** GPS_read ********************************/
/* @breif It read the logs from GPS module, then it check log names till it */
/* find the correct one, then it store the needed info from the log :       */
/* latitude , longitude , north or south , east or west and speed           */
/* this done by counter tracing the ',' character and based on counter we   */
/* we choose what to store. Storing is done in global variables             */
/* @parameters void                                                         */
/* @return     void                                                         */
/****************************************************************************/

