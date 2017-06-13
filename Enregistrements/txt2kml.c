#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>

void main(){


	FILE *pathFile,*parsedFile;
	char ch;
	clrscr();

	pathFile=fopen("pathFile.txt","r");
	parseFile=fopen("parsedFile.kml","w");
	
	fprintf(parsedFile,"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
	fprintf(parsedFile,"<kml xmlns=\"http://www.opengis.net/kml/2.2\">\n");
	fprintf(parsedFile,"  <Document>\n");
	fprintf(parsedFile,"    <name>Parcours IF23</name>\n");
	fprintf(parsedFile,"    <description>Tracing red paths on a map, from a TinyGPS object's data</description>\n");
	fprintf(parsedFile,"    <Style id=\"redLineredPoly\">\n");
	fprintf(parsedFile,"      <LineStyle>\n");
	fprintf(parsedFile,"        <color>501400ff</color>\n");
	fprintf(parsedFile,"        <width>4</width>\n");
	fprintf(parsedFile,"      </LineStyle>\n");
	fprintf(parsedFile,"      <PolyStyle>\n");
	fprintf(parsedFile,"        <color>501400ff</color>\n");
	fprintf(parsedFile,"      </PolyStyle>\n");
	fprintf(parsedFile,"    </Style>\n");
	fprintf(parsedFile,"    <Placemark>\n");
	fprintf(parsedFile,"      <name>IF23</name>\n");
	fprintf(parsedFile,"      <description>Red wall with red outlines</description>\n");
	fprintf(parsedFile,"      <styleUrl>#redLineredPoly</styleUrl>\n");
	fprintf(parsedFile,"      <LineString>\n");
	fprintf(parsedFile,"	    <extrude>1</extrude>\n");
	fprintf(parsedFile,"        <tessellate>1</tessellate>\n");
	fprintf(parsedFile,"        <altitudeMode>absolute</altitudeMode>\n");
	fprintf(parsedFile,"        <coordinates>\n");


	do {
      ch = fgetc(pathFile);
      fputc(ch, parsedFile);
   } while (ch != EOF);


	fprintf(parsedFile,"        </coordinates>\n");
	fprintf(parsedFile,"      </LineString>\n");
	fprintf(parsedFile,"    </Placemark>\n");
	fprintf(parsedFile,"  </Document>\n");
	fprintf(parsedFile,"</kml>\n");
        
     
	fcloseall();




}