#ifndef CLASS_H_INCLUDED
#define CLASS_H_INCLUDED
class Table{
protected :

///------------------------------------------------------------------------------------------------------------------------------
    /*Map table stores the information of all the VALID maps in the map
      The information  includes the pair of TOP LEFT co-ordinates and the x(j) and y(i) size of the map
      traversing each map would mean :
            for each y(i) do :
                for each x(j) do :
                    traverse[y][x]
      This table however does not store any information on the fringe maps
    */

    struct MapTable{
        int i; int j;
        int iSize;int jSize;
        MapTable *next;
    }*MTptr,*MTtop;

    //Creates a new Node and assigns it THE information
    MapTable *CreateEntry(int i,int j,int iSize, int jSize){
        MTptr = new MapTable;
        MTptr->i=i;
        MTptr->j=j;
        MTptr->iSize=iSize;
        MTptr->jSize=jSize;
        MTptr->next=NULL;
        return MTptr;
    }

    //Adds the entry to the Table
    void pushEntry(MapTable *np){ // Stack or LIFO approach
        if(MTtop==NULL)
            { MTtop=np;
            }else{
                MTptr=MTtop;
                MTtop=np;
                np->next=MTptr;
            }
        }
///------------------------------------------------------------------------------------------------------------------------------
    /*coOrdinates List stores the list of coOrdinates ,of a particular region in the Map
      The same conventions of i and j are preserved
      i.e. i representing the y co-ordinate
      and, j representing the x co-ordinate
      a status flag is also attached to each node */
    struct coOrdinates{
        int i;
        int j;
        bool status;
        coOrdinates *next;
    }*COptr,*COtop;

    //Creates a new Node and assigns it THE information
    coOrdinates *emergeCoOrdinate(int i,int j,bool status=false){
        COptr = new coOrdinates;
        COptr->i=i;
        COptr->j=j;
        COptr->status=status;
        COptr->next=NULL;
        return  COptr;
    }

     //Adds the entry to the Table
    void insertCoOrdinate(coOrdinates *np){// Stack or LIFO approach
       if( COtop==NULL)
            { COtop=np;
            }else{
               COptr= COtop;
               COtop=np;
               np->next= COptr;
            }
        }
///------------------------------------------------------------------------------------------------------------------------------

    struct FringeMapTable{
        int i1; int j1;
        int iSize;int jSize;
        int i2; int j2;

        FringeMapTable *next;
    }*FTptr,*FTtop,*FHTtop;

    FringeMapTable *CreateEntry(int i1,int j1,int i2,int j2,int iSize, int jSize){
        FTptr = new FringeMapTable;
        FTptr->i1=i1;
        FTptr->j1=j1;
        FTptr->i2=i2;
        FTptr->j2=j2;
        FTptr->iSize=iSize;
        FTptr->jSize=jSize;
        FTptr->next=NULL;
        return FTptr;
    }

    void pushEntry(FringeMapTable *np){
        if(FTtop==NULL){FTtop=np;}
        else{
            FTptr=FTtop;
            FTtop=np;
            np->next=FTptr;
        }
    }
    void pushHEntry(FringeMapTable *np){
        if(FHTtop==NULL){FHTtop=np;}
        else{
            FTptr=FHTtop;
            FHTtop=np;
            np->next=FTptr;
        }
    }

};
class KMap inherits Table{
    int Map[ROW][COLUMN];
    public:
    KMap();
    void MapGenerator();
    void FringeMapGenerator_Vertical();
    void FringeMapGenerator_Horizontal();
    void redundancyEliminator(int,int,int,int);
    void FringeRedundancyEliminator_Vertical(int,int,int,int,int,int);
    void FringeRedundancyEliminator_Horizontal(int,int,int,int,int,int);
    void displayMap(){
                                                                                                                                    MTptr=MTtop;
                                                                                                                                    while(MTptr!=NULL){
                                                                                                                                    cout<<"\nA map found from location "<<MTptr->i<<" "<<MTptr->j<<" of size "<<MTptr->iSize<<" "<<MTptr->jSize;
                                                                                                                                    MTptr=MTptr->next;
                                                                                                                                        }
        }
void FringeDisplayMap(){
                                                                                                                                    FTptr=FTtop;
                                                                                                                                    while(FTptr!=NULL){
                                                                                                                                    cout<<"\nA map found from location "<<FTptr->i1<<" "<<FTptr->j1<<" and"<<FTptr->i2<<" "<<FTptr->j2<<" of size "<<FTptr->iSize<<" "<<FTptr->jSize;
                                                                                                                                    FTptr=FTptr->next;
                                                                                                                                        }
        }

};


#endif // CLASS_H_INCLUDED
