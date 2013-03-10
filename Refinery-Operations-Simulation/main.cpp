//
// Project: Refinery Operations Simulation
// Author : FIRAT KARAKUSOGLU
// Email  : firatkarakusoglu@gmail.com
// Date   : 2007
//

#include <iostream>
#include <queue>
#include <string>
#include <stdlib.h>
#include <conio.h>
#include "f_graph.h"

using namespace std;

///////////////////////////////////////////////////////////////
char * combine(double _x, char * _someString)
{
    int x = static_cast<int>(_x);
    char *msg =  new char[strlen(_someString)+5];
    itoa(x,msg,10);
    return(strcat(msg,_someString));
    }

char * combine( char * _someString,double _x)
{
    int x = static_cast<int>(_x);
    char *msg =  new char[strlen(_someString)+5];
    itoa(x,msg,10);
    char *someString = new char[strlen(_someString)+1];
    strcpy(someString,_someString);
    return(strcat(someString,msg));
    }

char * combine(char * _someString1, char * _someString2)
{
    char *msg =  new char[strlen(_someString1)+strlen(_someString2)];
    return(strcat(_someString1,_someString2));
    }
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
class Ship
{
       public:
              Ship(double _capacity=100):capacity(_capacity)
              {
                    include = capacity;
                    doubleShipId++;
                    shipId = doubleShipId;
                    int _doubleShipId = static_cast<int>(doubleShipId);
                    itoa(_doubleShipId, chrShipId, 10);
                    strcpy(shipName,"Ship");
                    strcat(shipName,chrShipId);
              };
              char shipName[15];
              char chrShipId[10];
              double shipId;
              double capacity;
              double include;

              bool isEmpty(void) {return include<=0;};
              bool isFull(void){return include>=capacity;};
              bool load(void)
              {
                  if(!isFull()){include++; return true;}
                  else return false;
              };
              bool unload()
              {
                  if(!isEmpty()){include--; return true;}
                  else  return false;
              };

       private:
              static double doubleShipId;
};
double Ship::doubleShipId = 0;
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
class Tanker
{
       public:
              Tanker(double _capacity)
              {
                    include = 0;
                    if(_capacity>0) {capacity = _capacity; };
                    doubleTankerId++;
                    tankerId = doubleTankerId;
                    int _doubleTankerId = static_cast<int>(doubleTankerId);
                    itoa(_doubleTankerId, chrTankerId, 10);
                    strcpy(tankerName,"Tanker");
                    strcat(tankerName,chrTankerId);
              };
              char tankerName[15];
              char chrTankerId[10];
              double tankerId;
              double capacity;
              double include;

              bool isEmpty(void) {return include<=0;};
              bool isFull(void){return include>=capacity;};
              bool load(void)
              {
                  if(!isFull()){include++; return true;}
                  else return false;
              };
              bool unload(void)
              {
                  if(!isEmpty()){include--; return true;}
                  else  return false;
              };

       private:
              static double doubleTankerId;
};
double Tanker::doubleTankerId = 0;

class TankerFuilOil:public Tanker
{
      public:
      TankerFuilOil(double _capacity):Tanker(_capacity)
      {
         if(_capacity>0) capacity = _capacity;
         doubleTankerFuilOilId++;
         tankerFuilOilId = doubleTankerFuilOilId;
      }
      double capacity;
      double tankerFuilOilId;
      static double  doubleTankerFuilOilId;
};
double TankerFuilOil::doubleTankerFuilOilId = 0;

class TankerBenzine:public Tanker
{
      public:
      TankerBenzine(double _capacity):Tanker(_capacity)
      {
         if(_capacity>0) capacity = _capacity;
         doubleTankerBenzineId++;
         tankerBenzineId = doubleTankerBenzineId;
      }
      double capacity;
      double tankerBenzineId;
      static double  doubleTankerBenzineId;
};
double TankerBenzine::doubleTankerBenzineId = 0;
///////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////
class Tank
{
      public:
             Tank(double _capacity=200)
             {
                     include = 0;
                     capacity = 0;
                      if(_capacity>0) {capacity = _capacity;};
             };

             bool isEmpty(void) {return include<=0;};
             bool isFull(void){return include>=capacity;};
             bool load(void)
             {
                  if(!isFull()){include++; return true;}
                  else return false;
             };
             bool unload(void)
             {
                  if(!isEmpty()){include--; return true;}
                  else  return false;
             };

             double include;
             double capacity;
};

Tank bigTank,fuelOilTank ,benzineTank  ;
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
class refinery
{
      public:
      refinery
      (
              char *_rafName = "TUPRAS",
              double _shipCapacity = 5000, double _shipUnloadTime = 10,
              double _bigTankCapacity = 2000, double _bigTankUnloadTime = 10,
              double _fuelOilTankCapacity = 60, double _fuelOilTankUnloadTime = 4,
              double _benzineTankCapacity = 140, double _benzineTankUnloadTime = 7,
              double _fuelOilTankerCapacity = 100,
              double _benzineTankerCapacity = 700
              )
      {


          bigTank.capacity = _bigTankCapacity;
          fuelOilTank.capacity =  _fuelOilTankCapacity;
          benzineTank.capacity =  _benzineTankCapacity;

          shipCapacity = _shipCapacity;
          shipUnloadTime = _shipUnloadTime;
          bigTankCapacity = _bigTankCapacity;
          bigTankUnloadTime = _bigTankUnloadTime;
          fuelOilTankCapacity = _fuelOilTankCapacity;
          fuelOilTankUnloadTime = _fuelOilTankUnloadTime;
          benzineTankCapacity = _benzineTankCapacity;
          benzineTankUnloadTime = _benzineTankUnloadTime;
          fuelOilTankerCapacity = _fuelOilTankerCapacity;
          benzineTankerCapacity = _benzineTankerCapacity;
          rafName = _rafName;

          gf.headerLine(rafName);
          gf.showRightSide(combine("Ship Capacity..........: ",shipCapacity),1);
          gf.showRightSide(combine("Ship Unload Time.......: ",shipUnloadTime));
          gf.showRightSide(combine("Big Tank Capacity......: ",bigTank.capacity));
          gf.showRightSide(combine("Big Tank Unload Time...: ",bigTankUnloadTime));
          gf.showRightSide(combine("Fuel Oil Tank Capacity.: ",fuelOilTank.capacity));
          gf.showRightSide(combine("Fuel Oil Unload Time...: ",fuelOilTankUnloadTime));
          gf.showRightSide(combine("Benzine Tank Capacity..: ",benzineTank.capacity));
          gf.showRightSide(combine("Benzine Tank UnloadTime: ",benzineTankUnloadTime));
          gf.showRightSide("Refinery Has Been Done Succesfully.");
          gf.message("Press a Key to Start refinery");
          getch();
      };

          double shipCapacity ;
          double shipUnloadTime ;
          double bigTankCapacity ;
          double bigTankUnloadTime ;
          double fuelOilTankCapacity ;
          double fuelOilTankUnloadTime ;
          double benzineTankCapacity ;
          double benzineTankUnloadTime ;
          double fuelOilTankerCapacity ;
          double benzineTankerCapacity ;

      char * rafName;
      queue<Ship> ships;
      queue<TankerFuilOil> fuelOilTankers;
      queue<TankerBenzine> benzineTankers;



      void makeRows(double _numberOfShips=1, double _numberOfFuelOilTankers=1,
      double _numberOfBenzineTankers=1)
      {
         for(double i=0;i<_numberOfShips;i++){Ship s(shipCapacity); ships.push(s);};
         for(double i=0;i<_numberOfFuelOilTankers;i++)
         {
                 TankerFuilOil t(fuelOilTankerCapacity);
                 fuelOilTankers.push(t);
                 };
         for(double i=0;i<_numberOfBenzineTankers;i++)
         {
                 TankerBenzine t(benzineTankerCapacity);
                 benzineTankers.push(t);
                 };
      }
      double fillBigTank()//the raw oil will be loaded tanks from ships
      {
           //cout<<"...BIG TANK YUKLENIYOR...";
           double bigTankLoadAmountPerSecond = shipCapacity/shipUnloadTime;
           double ctr=0;

           if(bigTankCapacity >=(bigTank.include + bigTankLoadAmountPerSecond))
           {
                           while(ctr<bigTankLoadAmountPerSecond )
                           {
                           ctr++;
                           bigTank.load();
                           if(ships.front().unload()){}
                           else
                           {
                                     ships.pop();
                                     ships.front().unload();
                                     };
                           }
            }
            else{}//gf.footerLine("TASMA OLACAGINDAN GEMI BIG TANKA BOSALMADI");

            gf.showRightSide(ships.front().shipName,1);
            cout<<combine("Include:",ships.front().include);
      }
      double processBigTank()
      {
           double bigTankUnloadAmountPerSecond = bigTankCapacity/bigTankUnloadTime;
           double fuelOilTankLoadAmountPerSecond = (bigTankUnloadAmountPerSecond/10)*3;
           double benzineTankLoadAmountPerSecond = (bigTankUnloadAmountPerSecond/10)*7;

           double fuelOilTankUnloadAmountPerSecond = fuelOilTankCapacity/fuelOilTankUnloadTime;
           double benzineTankUnloadAmountPerSecond = benzineTankCapacity/benzineTankUnloadTime;

           double ctr=0;
           //while(ctr<=bigTankUnloadAmountPerSecond)
           //{
                //ctr++;
                if(!fuelOilTank.isFull() && fuelOilTank.capacity>=(fuelOilTank.include+fuelOilTankLoadAmountPerSecond))
                {
                      for(double i=0;i<fuelOilTankLoadAmountPerSecond;i++){bigTank.unload();fuelOilTank.load();}
                      fillFuelOilTankers(fuelOilTankUnloadAmountPerSecond);
                }
                //fuel oil tanki doldu - tankerlere bosalma islemi gerceklesiyor
                else
                {
                    //gf.footerLine("Fuel Oil Tank bosaliyor..");
                    //gf.showRightSide("FUEL OIL TANKI DOLDU-BOSALTMA YAPILIYOR");hata
                    fillFuelOilTankers(fuelOilTankUnloadAmountPerSecond);
                }

                if(!benzineTank.isFull() && benzineTank.capacity>=(benzineTank.include+benzineTankLoadAmountPerSecond))
                {
                      for(double i=0;i<benzineTankLoadAmountPerSecond;i++){bigTank.unload(); benzineTank.load();}
                      fillBenzineTankers(benzineTankUnloadAmountPerSecond);
                }
                //benzin tanki doldu - tankerlere bosalma islemi gerceklesiyor
                else
                {
                    //gf.footerLine("!!!BENZINE TANKI DOLDU-BOSALTMA YAPILIYOR");hata
                    fillBenzineTankers(benzineTankUnloadAmountPerSecond);
                }
                if(bigTank.isEmpty())
                {
                                     //gf.footerLine("Big Tank is Empty");
                                     //fillBigTank();
                };
                gf.showRightSide("");
                gf.showRightSide("TANKS");
                gf.showRightSide("Big Tank : ");cout<<bigTank.include;//
                gf.showRightSide("Fuel Oil Tank: ");cout<< fuelOilTank.include;//
                gf.showRightSide("Benzine Tank: ");cout<<benzineTank.include;//
                gf.showRightSide("");
                gf.showRightSide("TANKERS");
                gf.showRightSide("");cout<<combine(fuelOilTankers.front().tankerFuilOilId,". Fuel Tanker ")<<combine("Include: ",fuelOilTankers.front().include);
                gf.showRightSide("");cout<<combine(benzineTankers.front().tankerBenzineId,". Benzine Tanker ")<<combine("Include: ",benzineTankers.front().include);

                gf.wait(1000);
                 //getch();
           //}
      }
      double fillFuelOilTankers(double fuelOilAmountToLoad)
      {
          double ctr=0;
           //cout<<"Tanklar Tankerlere Bosaliyor..."<<endl;

           while(ctr<fuelOilAmountToLoad)
           {
                if(fuelOilTankers.front().capacity > fuelOilTankers.front().include)
                {
                     fuelOilTankers.front().load();
                     //cout<<"*FUEL OIL TANKERI ICINDE: "<<fuelOilTankers.front().include<<endl;
                     fuelOilTank.unload();
                     }//fuel oil tankeri load ediliyor
                else //siradaki diger tankere geciliyor
                {
                    //gf.showRightSide(combine(fuelOilTankers.front().tankerFuilOilId,". Tanker Doldu."));hata
                    makeRows(0,1,0);
                    fuelOilTankers.pop();
                    fuelOilTankers.front().load();
                    fuelOilTank.unload();
                    //gf.showRightSide(combine(fuelOilTankers.front().tankerFuilOilId,". Siradaki Fuel Tankeri Geldi."));
                };
                ctr++;
           }

           ////////////////////////////////////////////////////////////////////////
          }

          double fillBenzineTankers(double benzineAmountToLoad)
          {
          double ctr=0;
           //cout<<"Tanklar Tankerlere Bosaliyor..."<<endl;

           while(ctr<benzineAmountToLoad)
           {
                if(benzineTankers.front().capacity > benzineTankers.front().include)
                {
                     benzineTankers.front().load();
                     //cout<<"*FUEL OIL TANKERI ICINDE: "<<benzineTankers.front().include<<endl;
                     benzineTank.unload();
                     }//fuel oil tankeri load ediliyor
                else //siradaki diger tankere geciliyor
                {
                    //gf.showRightSide(combine(benzineTankers.front().tankerBenzineId,". Tanker Doldu."));hata
                    makeRows(0,0,1);
                    benzineTankers.pop();
                    benzineTankers.front().load();
                    benzineTank.unload();
                    //gf.showRightSide(combine(benzineTankers.front().tankerBenzineId,". Siradaki Benzine Tankeri Geldi."));
                };
                ctr++;
           }
      }
};
refinery *r1;
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
void takeRafInfos()
{

     gf.headerLine("Refinery being built...");

     char* rafInfo1 = new char[20];
     gf.footerLine("refineryName: ");
     cin>>rafInfo1;
     gf.showRightSide(rafInfo1,1);

     double rafInfo2;
     gf.footerLine("ShipsCapacity: ");
     cin>>rafInfo2;
     gf.showRightSide(combine(":",rafInfo2),1);

     double rafInfo3;
     gf.footerLine("Ships Unload Time: ");
     cin>>rafInfo3;
     gf.showRightSide(combine(":",rafInfo3),1);

     double rafInfo4;
     gf.footerLine("Big Tank Capacity: ");
     cin>>rafInfo4;
     gf.showRightSide(combine(":",rafInfo4),1);

     double rafInfo5;
     gf.footerLine("Big Tank Unload Time: ");
     cin>>rafInfo5;
     gf.showRightSide(combine(":",rafInfo5),1);

     double rafInfo6;
     gf.footerLine("Fuel Tank Capacity: ");
     cin>>rafInfo6;
     gf.showRightSide(combine(":",rafInfo6),1);

     double rafInfo7;
     gf.footerLine("Fuel Tank Unload Time: ");
     cin>>rafInfo7;
     gf.showRightSide(combine(":",rafInfo7),1);

     double rafInfo8;
     gf.footerLine("Benzine Tank Capacity: ");
     cin>>rafInfo8;
     gf.showRightSide(combine(":",rafInfo8),1);

     double rafInfo9;
     gf.footerLine("BenzineTankUnload:");//BenzineTank Unload Time:
     cin>>rafInfo9;
     gf.showRightSide(combine("",rafInfo9),1);

     double rafInfo10;
     gf.footerLine("FuelTankers Capacity: ");
     cin>>rafInfo10;
     gf.showRightSide(combine(":",rafInfo10),1);

     double rafInfo11;
     gf.footerLine("BenzineTankers Capacity: ");
     cin>>rafInfo11;
     gf.showRightSide(combine(": ",rafInfo11),1);
     r1 = new refinery(rafInfo1,rafInfo2,rafInfo3,rafInfo4,rafInfo5,rafInfo6,rafInfo7,rafInfo8,rafInfo9,rafInfo10,rafInfo11);
     }

     void showRafInfos(refinery *raf)
     {
          gf.headerLine((*r1).rafName);
          gf.showLeftSide("Capacity",1);cout<<"Time";
          gf.showLeftSide("----------------");
          gf.showLeftSide(combine("Ship:",(*r1).shipCapacity));cout<<(*r1).shipUnloadTime;
          gf.showLeftSide("----------------");
          gf.showLeftSide(combine("BigTank:",(*r1).bigTankCapacity));cout<<(*r1).bigTankUnloadTime;
          gf.showLeftSide(combine("FOilTank:",(*r1).fuelOilTankCapacity));cout<<(*r1).fuelOilTankUnloadTime;
          gf.showLeftSide(combine("BnzTank:",(*r1).benzineTankCapacity));cout<<(*r1).benzineTankUnloadTime;
          gf.showLeftSide("----------------");
          gf.showLeftSide(combine("FOilTanker:",(*r1).fuelOilTankerCapacity));
          gf.showLeftSide(combine("BnzTanker:",(*r1).benzineTankerCapacity));
          }
///////////////////////////////////////////////////////////////

int main()
{


    char *confirmation = new char[10];
    gf.makeSkeleton();
    gf.setTitle("                                      Refinery Simulation by FIRAT KARAKUSOGLU");
    gf.footerLine("Do you want to set with default refinery values [Y/N]: ");
    cin>>confirmation;
    while(!(confirmation[0] == 'Y' || confirmation[0] == 'y' ||  confirmation[0] == 'N' || confirmation[0] == 'n'))
    {
                       gf.warning("Error: Press Y or N!");
                       gf.footerLine("Do you want to set with default refinery values [Y/N]: ");
                       cin>>confirmation;
                       }

    if(confirmation[0] == 'N' || confirmation[0] == 'n'){takeRafInfos();}
    if(confirmation[0] == 'Y' || confirmation[0] == 'y') r1 = new refinery();

    (*r1).makeRows();
    double processTime = 0; //how many seconds, refinery run
    while(1==1)
    {
                         processTime++;
                         if(processTime == 1)showRafInfos(r1);
                         gf.rightBottomText(combine(processTime,". Second"));
                         gf.footerLine("");
                         (*r1).fillBigTank();
                         (*r1).processBigTank();
    }
};

