#include "menu.h"
#include <Arduino.h>

 void generateMenu(Menu* menu, Model* model, MENU_TYPE menu_type)
 {
   menu->menu_type=menu_type;
   ShowModel showModel;
   initShowModel(&showModel);
   modelToShowModel(model, &showModel);
	 char cases[16]="";
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
	 menu->configureMode=FALSE;
	 menu->maxSelectionGroupId=-1;
	 switch(menu_type) {
		 case ACCUEIL :
			 strupdate(cases,0,showModel.localShowDateTime.hour,2);
			 strupdate(cases,2,":",1);
			 strupdate(cases,3,showModel.localShowDateTime.minute,2);
			 strupdate(cases,5,":",1);
			 strupdate(cases,6,showModel.localShowDateTime.second,2);
			 strupdate(cases,8,"BAT:",4);
			 strupdate(cases,12,showModel.autonomy,3);
			 strupdate(cases,15,"%",1);
			 menu->isConfigurable=FALSE;
		 break;
		 case DATE :
			 strupdate(cases,0,"SD",2);
       strupdate(cases,2," ",1);
			 strupdate(cases,3,showModel.localShowDateTime.day,2);
			 strupdate(cases,5," ",1);
			 strupdate(cases,6,showModel.localShowDateTime.month,2);
			 strupdate(cases,8,showModel.isSDOK,2);
       strupdate(cases,10,"  ",2);
			 strupdate(cases,12,showModel.localShowDateTime.year,4);
			 menu->isConfigurable=FALSE;
		 break;
		 case PARCOURS :
			 strupdate(cases,0,"PARCOURS",8);
			 strupdate(cases,8,showModel.durationParcours,8);
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
			 strupdate(cases,0,"INTERVms",8);
       strupdate(cases,8,showModel.durationInterval,8);
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
			 strupdate(cases,0,"LA",2);
			 strupdate(cases,2,showModel.latitude,6);
			 strupdate(cases,8,"LO",2);
			 strupdate(cases,10,showModel.longitude,6);
			 menu->isConfigurable=FALSE;
		 break; 
		 case COORDS2 :
			 strupdate(cases,0,"AL",2);
			 strupdate(cases,2,showModel.altitude,6);
			 strupdate(cases,8,"CO",2);
			 strupdate(cases,10,showModel.course,6);
			 menu->isConfigurable=FALSE;
		 break;
		 case COORDS3 :
			 strupdate(cases,0,"SP",2);
			 strupdate(cases,2,showModel.speed,6);
			 strupdate(cases,8,"SATT ",5);
			 strupdate(cases,13,showModel.satellites,2);
			 menu->isConfigurable=FALSE;
		 break;
		 case COORDS4 :
			 strupdate(cases,0,"HD",2);
			 strupdate(cases,2,showModel.hdop,6);
			 strupdate(cases,8,"        ",8);
			 menu->isConfigurable=FALSE;
		 break;
		 case ENR1:
			 strupdate(cases,0,"START   ",8);
			 strupdate(cases,8,"STOP    ",8);
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
			 strupdate(cases,0,showModel.recordFilename,16);
			 menu->isConfigurable=FALSE;
		 break;
		 default :
			 strupdate(cases,0,"SECRET  MENU",12);
			 menu->isConfigurable=FALSE;
		 break;
	 }
   if(menu->isConfigurable == TRUE) {
     menu->selectedIDGroup=0;
   } else {
     menu->selectedIDGroup=-1;
   }
   strupdate(menu->cases,0,cases,16);
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

void increaseSelection(Menu* menu)
{
  menu->selectedIDGroup=(menu->selectedIDGroup + 1)%(menu->maxSelectionGroupId+1);
}

void increaseSelectedConfigValue(Menu* menu, Model* model)
{
  switch(menu->menu_type) {
     case PARCOURS :
       switch(menu->selectedIDGroup) {
        case 0 :
          model->durationParcours+=3600;
          break;
        case 1 :
          model->durationParcours+=60;
          break;
        case 2 :
           model->durationParcours++;
           break;
        default :
          break;
       }
     break; 
     case INTERVAL :
       switch(menu->selectedIDGroup) {
        case 0 :
          model->durationInterval+=6000;
          break;
        case 1 :
          model->durationInterval+=100;
          break;
        case 2 :
          model->durationInterval++;
          break;
        default :
          break;
       }
     break;
     case ENR1:
     break;
   }
   model->durationParcours%=99*3600;
   model->durationInterval%=99*6000;
}

void updateMenuCases(Menu* menu, Model* model)
{
   ShowModel showModel;
   initShowModel(&showModel);
   modelToShowModel(model, &showModel);
   char cases[16]="";
   switch(menu->menu_type) {
     case ACCUEIL :
       strupdate(cases,0,showModel.localShowDateTime.hour,2);
       strupdate(cases,2,":",1);
       strupdate(cases,3,showModel.localShowDateTime.minute,2);
       strupdate(cases,5,":",1);
       strupdate(cases,6,showModel.localShowDateTime.second,2);
       strupdate(cases,8,"BAT:",4);
       strupdate(cases,12,showModel.autonomy,3);
       strupdate(cases,15,"%",1);
     break;
     case DATE :
       strupdate(cases,0,"SD",2);
       strupdate(cases,2," ",1);
       strupdate(cases,3,showModel.localShowDateTime.day,2);
       strupdate(cases,5," ",1);
       strupdate(cases,6,showModel.localShowDateTime.month,2);
       strupdate(cases,8,showModel.isSDOK,2);
       strupdate(cases,10,"  ",2);
       strupdate(cases,12,showModel.localShowDateTime.year,4);
     break;
     case PARCOURS :
       strupdate(cases,0,"PARCOURS",8);
       strupdate(cases,8,showModel.durationParcours,8);
     break; 
     case INTERVAL :
       strupdate(cases,0,"INTERVms",8);
       strupdate(cases,8,showModel.durationInterval,8);
     break;
     case COORDS1 :
       strupdate(cases,0,"LA",2);
       strupdate(cases,2,showModel.latitude,6);
       strupdate(cases,8,"LO",2);
       strupdate(cases,10,showModel.longitude,6);
     break; 
     case COORDS2 :
       strupdate(cases,0,"AL",2);
       strupdate(cases,2,showModel.altitude,6);
       strupdate(cases,8,"CO",2);
       strupdate(cases,10,showModel.course,6);
     break;
     case COORDS3 :
       strupdate(cases,0,"SP",2);
       strupdate(cases,2,showModel.speed,6);
       strupdate(cases,8,"SATT ",5);
       strupdate(cases,13,showModel.satellites,2);
     break;
     case COORDS4 :
       strupdate(cases,0,"HD",2);
       strupdate(cases,2,showModel.hdop,6);
       strupdate(cases,8,"        ",8);
     break;
     case ENR1:
       strupdate(cases,0,"START   ",8);
       strupdate(cases,8,"STOP    ",8);
       menu->isConfigurable=TRUE;
     break;
     case ENR2:
       strupdate(cases,0,showModel.recordFilename,16);
     break;
     default :
       strupdate(cases,0,"SECRET  MENU",12);
     break;
   }
   strupdate(menu->cases,0,cases,16);
}

