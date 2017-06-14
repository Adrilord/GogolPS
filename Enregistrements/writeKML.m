% ouverture de fichier
%fid = fopen('enrUno1206');
%fid = fopen('enrDos1206');
fid = fopen('enrTres1206');

Datas= fscanf(fid,'%f,%f,%f,%f,%f,%f,%f,%f\n',[8 Inf]); %on lit les données
sizeEnr = size(Datas); %dimensions d'enregistrements
fclose(fid); % fermeture de fichier

%ouverture du fichier résulant
KMLresult = fopen('result.txt','at');

fprintf(KMLresult,"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
	fprintf(KMLresult,"<kml xmlns=\"http://www.opengis.net/kml/2.2\">\n");
	fprintf(KMLresult,"  <Document>\n");
	fprintf(KMLresult,"    <name>Parcours IF23</name>\n");
	fprintf(KMLresult,"    <description>Tracing red paths on a map, from a TinyGPS object's data</description>\n");
	fprintf(KMLresult,"    <Style id=\"redLineredPoly\">\n");
	fprintf(KMLresult,"      <LineStyle>\n");
	fprintf(KMLresult,"        <color>501400ff</color>\n");
	fprintf(KMLresult,"        <width>10</width>\n");
	fprintf(KMLresult,"      </LineStyle>\n");
	fprintf(KMLresult,"      <PolyStyle>\n");
	fprintf(KMLresult,"        <color>501400ff</color>\n");
	fprintf(KMLresult,"      </PolyStyle>\n");
	fprintf(KMLresult,"    </Style>\n");
	fprintf(KMLresult,"    <Placemark>\n");
	fprintf(KMLresult,"      <name>IF23</name>\n");
	fprintf(KMLresult,"      <description>Red wall with red outlines</description>\n");
	fprintf(KMLresult,"      <styleUrl>#redLineredPoly</styleUrl>\n");
	fprintf(KMLresult,"      <LineString>\n");
	fprintf(KMLresult,"	    <extrude>1</extrude>\n");
	fprintf(KMLresult,"        <tessellate>1</tessellate>\n");
	fprintf(KMLresult,"        <altitudeMode>absolute</altitudeMode>\n");
	fprintf(KMLresult,"        <coordinates>\n");
  for i=1:sizeEnr(1,2)
    fprintf(KMLresult,"         %f,%f,%f\n",Datas(1,i),Datas(2,i),Datas(3,i));
  end
	fprintf(KMLresult,"        </coordinates>\n");
	fprintf(KMLresult,"      </LineString>\n");
	fprintf(KMLresult,"    </Placemark>\n");
	fprintf(KMLresult,"  </Document>\n");
	fprintf(KMLresult,"</kml>\n");

  fclose(KMLresult);