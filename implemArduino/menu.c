#include "menu.h"

void showMenu(Menu menu)
{
	for(int i=0; i<NUMBER_OF_CASES/2; i++) {
		Serial.print(menu.cases[i]);
	}
	Serial.print("\n");
	for(int i=NUMBER_OF_CASES/2; i<NUMBER_OF_CASES; i++) {
		Serial.print(menu.cases[i]);
	}
  Serial.print("\n");
}

 void generateMenu(Menu* menu, ShowModel* showModel, MENU_TYPE menu_type)
 {
	 char cases[17]="\0";
	 menu->selectionIDGroupCases[0]=-1;
	 menu->selectionIDGroupCases[1]=-1;
	 menu->selectionIDGroupCases[2]=-1;
	 menu->selectionIDGroupCases[3]=-1;
	 menu->selectionIDGroupCases[4]=-1;
	 menu->selectionIDGroupCases[5]=-1;
	 menu->selectionIDGroupCases[6]=-1;
	 menu->selectionIDGroupCases[7]=-1;
	 menu->selectionIDGroupCases[8]=-1;
	 menu->selectionIDGroupCases[9]=-1;
	 menu->selectionIDGroupCases[10]=-1;
	 menu->selectionIDGroupCases[11]=-1;
	 menu->selectionIDGroupCases[12]=-1;
	 menu->selectionIDGroupCases[13]=-1;
	 menu->selectionIDGroupCases[14]=-1;
	 menu->selectionIDGroupCases[15]=-1;
	 menu->configureMode=NORMAL;
	 menu->maxSelectionGroupId=-1;
	 switch(menu_type) {
		 case ACCUEIL :
			 strupdate(cases,0,showModel->localShowDateTime.hour,2);
			 strupdate(cases,1,":",1);
			 strupdate(cases,2,showModel->localShowDateTime.minute,2);
			 strupdate(cases,4,":",);
			 strupdate(cases,5,showModel->localShowDateTime.second,2);
			 strupdate(cases,7,"BAT:",4);
			 strupdate(cases,11,showModel->autonomy,3);
			 strupdate(cases,14,"%",1);
			 menu->isConfigurable=FALSE;
		 break;
		 case DATE :
			 strupdate(cases,17,"   ");
			 strupdate(cases,17,showModel->localShowDateTime.day);
			 strupdate(cases,17," ");
			 strupdate(cases,17,showModel->localShowDateTime.month);
			 strupdate(cases,17,"    ");
			 strupdate(cases,17,showModel->localShowDateTime.year);
			 menu->isConfigurable=TRUE;
			 menu->selectionIDGroupCases[3]=0;
			 menu->selectionIDGroupCases[4]=0;
			 menu->selectionIDGroupCases[6]=1;
			 menu->selectionIDGroupCases[7]=1;
			 menu->selectionIDGroupCases[12]=2;
			 menu->selectionIDGroupCases[13]=2;
			 menu->selectionIDGroupCases[14]=2;
			 menu->selectionIDGroupCases[15]=2;
			 menu->maxSelectionGroupId=2;
		 break;
		 case PARCOURS :
			 strupdate(cases,17,"PARCOURS");
			 strupdate(cases,17,showModel->durationParcours);
			 menu->isConfigurable=TRUE;
			 menu->selectionIDGroupCases[8]=0;
			 menu->selectionIDGroupCases[9]=0;
			 menu->selectionIDGroupCases[11]=1;
			 menu->selectionIDGroupCases[12]=1;
			 menu->selectionIDGroupCases[14]=2;
			 menu->selectionIDGroupCases[15]=2;
			 menu->maxSelectionGroupId=2;
		 break; 
		 case INTERVAL :
			 strupdate(cases,17,"INTERVms");
			 strupdate(cases,17,showModel->durationInterval);
			 menu->isConfigurable=TRUE;
			 menu->selectionIDGroupCases[8]=0;
			 menu->selectionIDGroupCases[9]=0;
			 menu->selectionIDGroupCases[11]=1;
			 menu->selectionIDGroupCases[12]=1;
			 menu->selectionIDGroupCases[14]=2;
			 menu->selectionIDGroupCases[15]=2;
			 menu->maxSelectionGroupId=2;
		 break;
		 case COORDS1 :
			 strupdate(cases,17,"LA");
			 strupdate(cases,17,showModel->latitude);
			 strupdate(cases,17,"LO");
			 strupdate(cases,17,showModel->longitude);
			 menu->isConfigurable=FALSE;
		 break; 
		 case COORDS2 :
			 strupdate(cases,17,"AL");
			 strupdate(cases,17,showModel->altitude);
			 strupdate(cases,17,"CO");
			 strupdate(cases,17,showModel->course);
			 menu->isConfigurable=FALSE;
		 break;
		 case COORDS3 :
			 strupdate(cases,17,"SP");
			 strupdate(cases,17,showModel->speed);
			 strupdate(cases,17,"SATT  ");
			 strupdate(cases,17,showModel->satellites);
			 menu->isConfigurable=FALSE;
		 break;
		 case COORDS4 :
			 strupdate(cases,17,"HD");
			 strupdate(cases,17,showModel->hdop);
			 strupdate(cases,17,"        ");
			 menu->isConfigurable=FALSE;
		 break;
		 case ENR1:
			 strupdate(cases,17,"START   ");
			 strupdate(cases,17,"STOP    ");
			 menu->isConfigurable=TRUE;
			 menu->selectionIDGroupCases[0]=0;
			 menu->selectionIDGroupCases[1]=0;
			 menu->selectionIDGroupCases[2]=0;
			 menu->selectionIDGroupCases[3]=0;
			 menu->selectionIDGroupCases[4]=0;
			 menu->selectionIDGroupCases[8]=1;
			 menu->selectionIDGroupCases[9]=1;
			 menu->selectionIDGroupCases[10]=1;
			 menu->selectionIDGroupCases[11]=1;
			 menu->maxSelectionGroupId=1;
		 break;
		 case ENR2:
			 strupdate(cases,showModel->recordFilename);
			 menu->isConfigurable=FALSE;
		 break;
		 default :
			 strupdate(cases,"SECRET  MENU");
			 menu->isConfigurable=FALSE;
		 break;
	 }
	 printf("TEST1 \n");
	 printf(cases);
	 printf("\n");
	 strcpy(menu->cases,"              ");
	 snprintf(menu->cases,17,cases);
	 printf("TEST2 \n");
	 printf(menu->cases);
	 printf("\n");
 }

void interconnexions(Menu menus[10])
{
	menus[ACCUEIL].sw1Connection = &menus[PARCOURS];
	menus[ACCUEIL].sw2Connection = &menus[DATE];
	menus[DATE].sw1Connection = &menus[PARCOURS];
	menus[DATE].sw2Connection = &menus[ACCUEIL];
	menus[PARCOURS].sw1Connection = &menus[COORDS1];
	menus[PARCOURS].sw2Connection = &menus[INTERVAL];
	menus[INTERVAL].sw1Connection = &menus[COORDS1];
	menus[INTERVAL].sw2Connection = &menus[PARCOURS];
	menus[COORDS1].sw1Connection = &menus[ENR1];
	menus[COORDS1].sw2Connection = &menus[COORDS2];
	menus[COORDS2].sw1Connection = &menus[ENR1];
	menus[COORDS2].sw2Connection = &menus[COORDS3];
	menus[COORDS3].sw1Connection = &menus[ENR1];
	menus[COORDS3].sw2Connection = &menus[COORDS4];
	menus[COORDS4].sw1Connection = &menus[ENR1];
	menus[COORDS4].sw2Connection = &menus[COORDS1];
	menus[ENR1].sw1Connection = &menus[ACCUEIL];
	menus[ENR1].sw2Connection = &menus[ENR2];
	menus[ENR2].sw1Connection = &menus[ACCUEIL];
	menus[ENR2].sw2Connection = &menus[ENR1];
}
