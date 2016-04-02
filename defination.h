
KMap::KMap(){

        //setting the HEADER pointers to NULL, Indicating an empty NODE
        MTtop=NULL; COtop=NULL; FTtop=NULL; FHTtop=NULL;

        //Initializing all co-ordinates to 1
        for(int i=0;i<ROW;i++){
            for(int j=0;j<COLUMN;j++){
                Map[i][j]=1;
                }
            }


        //Displaying the Map
        for(int i=0;i<ROW;i++){
            for(int j=0;j<COLUMN;j++){
                cout<<Map[i][j]<<" ";
                }cout<<"\n";
            }
        }


/*This function is the heart of the program, it is designed to identify all possible maps in the Map*/
void KMap::MapGenerator(){

        //Traversing each element of the Map
        for(int i=0;i<ROW;i++){
            for(int j=0;j<COLUMN;j++){
                //A search for a Map of 1s cannot start with zero, common thats obvious
                if(Map[i][j]==0)continue;

                ///DECIDING THE SIZE OF THE MAP
                /*here a contraction of the size is adopted
                which means the possibility is always tested for the Maximum map in the beginning
                i.e a ROW X COLUMN size
                the possibility gets reduced by a factor of two (prioritizing the x(j) side by mere choice)
                till a Map is found*/
                for(int iSize=ROW;iSize>0;iSize/=2){
                    for(int jSize=COLUMN;jSize>0;jSize/=2){
                        bool isMapped=true;

                        //If the attempted Mapping exceeds the dimension of the Map
                        if((i+iSize>ROW)||(j+jSize>COLUMN))continue;

                        //Traversing the region (where theres a possibility of Map with dimensions iSize and jSize)
                        for(int ti=i;ti<i+iSize;ti++){
                            for(int tj=j;tj<j+jSize;tj++){
                                if(Map[ti][tj]==0)isMapped=false;
                            }
                        }

                        if(isMapped==true){ //If the region consists of all 1s
                            //cout<<"\nA map found from location "<<i<<" "<<j<<" of size "<<iSize<<" "<<jSize;
                            ///THE DECISION FOR ADDING TO THE MAP TABLE
                            /*Being too good at its job, comes with its pitfall for our Mapgenerator
                              the function generates just too many Maps , than thats really needed
                              But thats not for it to care, as it has got its best buddy at help
                              the redundancyEliminator eliminates all the repeated or unnecessary maps...
                              and delivers a clean input to the Map table*/
                            ///The filter
                            redundancyEliminator(i,j,iSize,jSize);
                        }
                    }
                }
            }
        }
    }

  void KMap::redundancyEliminator(int i,int j, int iSize , int jSize){

            //setting the HEADER pointer to NULL, Indicating an empty NODE
            COtop=NULL;

            //Creating the List of co-ordinates for the requested Map
            for(int r=i;r<i+iSize;r++){
                for(int s=j;s<j+jSize;s++){
                    insertCoOrdinate(emergeCoOrdinate(r,s));
                    }
                }

            /*Theres no controversy with the first element ,
             so it goes as an entry to the Map table anyways */
            if(MTtop==NULL){
                pushEntry(CreateEntry(i,j,iSize,jSize));
                           }else{
                                MTptr=MTtop;
                                //Traversing each entry of the Map table
                                while(MTptr!=NULL){
                                    //For each entry , traversing all elements of the entry
                                    for(int r= MTptr->i;r < MTptr->i + MTptr->iSize;r++){
                                        for(int s= MTptr->j;s < MTptr->j + MTptr->jSize; s++){
                                            COptr= COtop;
                                          /*traversing the list of co-ordinates
                                            each element of individual entry of the map table is compared with the whole list of co-ordinates*/
                                            while( COptr!=NULL ){
                                                if(( COptr->i==r)&&( COptr->j==s)){
                                                    COptr->status=true;
                                                }
                                                COptr= COptr->next;
                                                }
                                            }
                                        }
                                        MTptr=MTptr->next;
                                    }

                                COptr= COtop;
                                while( COptr!=NULL){
                                    if( COptr->status==false){ //If any one of the element in the List of co-ordinates is not mapped
                                        pushEntry(CreateEntry(i,j,iSize,jSize));//Then add the Map to the Map table
                                        break;
                                        }
                                    COptr= COptr->next;
                                    }
                                }


    }

/*This function is the heart of the program, it is designed to identify all possible maps in the Map*/
 void KMap::FringeMapGenerator_Vertical(){
    //Traversing each element of the Map
    for(int rowSelect=0;rowSelect<ROW;rowSelect++){
        //A search for a Map of 1s cannot start with zero, common thats obvious
        if(Map[rowSelect][0]==0)continue;

            ///DECIDING THE SIZE OF THE MAP
                /*here a contraction of the size is adopted
                which means the possibility is always tested for the Maximum map in the beginning
                i.e a ROW X COLUMN size
                the possibility gets reduced by a factor of two (prioritizing the x(j) side by mere choice)
                till a Map is found*/
            for(int iSize=ROW;iSize>0;iSize/=2){
                for(int jSize=(COLUMN)/2;jSize>0;jSize/=2){
                    bool isMappedOne=true;
                    bool isMappedTwo=true;

                    //If the attempted Mapping exceeds the dimension of the Map
                    if((rowSelect+iSize>ROW))continue;

                    //Traversing the region (where theres a possibility of Map with dimensions iSize and jSize)
                    for(int i=rowSelect;i<rowSelect+iSize;i++){
                        for(int j=0;j<jSize;j++){
                            if(Map[i][j]==0)isMappedOne=false;
                            }
                        }
                        for(int i=rowSelect;i<rowSelect+iSize;i++){
                            for(int j=COLUMN-1;j>= COLUMN-jSize;j--){
                                if(Map[i][j]==0)isMappedTwo=false;
                            }
                        }

                        if(isMappedOne==true && isMappedTwo==true){//If the region consists of all 1s
                            //cout<<"\nA map found from location "<<rowSelect<<" 0"<<" of size "<<iSize<<" "<<jSize<<" and form "<<rowSelect<<" "<<COLUMN-1;
                             ///THE DECISION FOR ADDING TO THE MAP TABLE
                            /*Being too good at its job, comes with its pitfall for our Mapgenerator
                              the function generates just too many Maps , than thats really needed
                              But thats not for it to care, as it has got its best buddy at help
                              the redundancyEliminator eliminates all the repeated or unnecessary maps...
                              and delivers a clean input to the Map table*/
                            ///The filter
                            FringeRedundancyEliminator_Vertical(rowSelect,0,rowSelect,COLUMN-1,iSize,jSize);

                        }
                }
            }

    }
 }

void KMap::FringeRedundancyEliminator_Vertical(int i1,int j1,int i2,int j2, int iSize , int jSize){

                           //setting the HEADER pointer to NULL, Indicating an empty NODE
            COtop=NULL;

            //Creating the List of co-ordinates for the requested Map
            for(int r=i1;r<i1+iSize;r++){
                for(int s=j1;s<j1+jSize;s++){
                    insertCoOrdinate(emergeCoOrdinate(r,s));
                    }
                }

            /*Theres no controversy with the first element ,
             so it goes as an entry to the Map table anyways */
            if(FTtop==NULL){
                pushEntry(CreateEntry(i1,j1,i2,j2,iSize,jSize*2));
                           }else{
                                FTptr=FTtop;
                                //Traversing each entry of the Map table
                                while(FTptr!=NULL){
                                    //For each entry , traversing all elements of the entry
                                    for(int r= FTptr->i1;r < FTptr->i1 + FTptr->iSize;r++){
                                        for(int s= FTptr->j1;s < FTptr->j1 + FTptr->jSize; s++){
                                            COptr= COtop;
                                          /*traversing the list of co-ordinates
                                            each element of individual entry of the map table is compared with the whole list of co-ordinates*/
                                            while( COptr!=NULL ){
                                                if(( COptr->i==r)&&( COptr->j==s)){
                                                    COptr->status=true;
                                                }
                                                COptr= COptr->next;
                                                }
                                            }
                                        }
                                       FTptr=FTptr->next;
                                    }

                                COptr= COtop;
                                while( COptr!=NULL){
                                    if( COptr->status==false){ //If any one of the element in the List of co-ordinates is not mapped
                                        pushEntry(CreateEntry(i1,j1,i2,j2,iSize,jSize*2));//Then add the Map to the Map table
                                        break;
                                        }
                                    COptr= COptr->next;
                                    }
                                }



}

/*This function is the heart of the program, it is designed to identify all possible maps in the Map*/
void KMap::FringeMapGenerator_Horizontal(){
    for(int columnSelect=0;columnSelect<COLUMN;columnSelect++){
            //Traversing each element of the Map
            if(Map[0][columnSelect]==0)continue;

            ///DECIDING THE SIZE OF THE MAP
                /*here a contraction of the size is adopted
                which means the possibility is always tested for the Maximum map in the beginning
                i.e a ROW X COLUMN size
                the possibility gets reduced by a factor of two (prioritizing the x(j) side by mere choice)
                till a Map is found*/
            for(int iSize=ROW/2;iSize>0;iSize/=2){
                for(int jSize=COLUMN;jSize>0;jSize/=2){
                    bool isMappedOne=true;
                    bool isMappedTwo=true;


                    //If the attempted Mapping exceeds the dimension of the Map
                    if((columnSelect+jSize>COLUMN))continue;

                    //Traversing the region (where theres a possibility of Map with dimensions iSize and jSize)
                    for(int i=0;i<iSize;i++){
                        for(int j=columnSelect;j<columnSelect+jSize;j++){
                                if(Map[i][j]==0)isMappedOne=false;
                            }
                        }
                        for(int i=ROW-1;i>=ROW-iSize;i--){
                            for(int j=columnSelect;j<columnSelect+jSize;j++){
                                if(Map[i][j]==0)isMappedTwo=false;
                            }
                        }

                        if(isMappedOne==true && isMappedTwo==true){//If the region consists of all 1s
                            //cout<<"\nA map found from location "<<" 0 "<<columnSelect<<" of size "<<iSize<<" "<<jSize<<" and form "<<ROW-1<<" "<<columnSelect;
                            ///THE DECISION FOR ADDING TO THE MAP TABLE
                            /*Being too good at its job, comes with its pitfall for our Mapgenerator
                              the function generates just too many Maps , than thats really needed
                              But thats not for it to care, as it has got its best buddy at help
                              the redundancyEliminator eliminates all the repeated or unnecessary maps...
                              and delivers a clean input to the Map table*/
                            ///The filter
                            FringeRedundancyEliminator_Horizontal(0,columnSelect,ROW-1,columnSelect,iSize,jSize);

                        }
                }
            }

    }
    FTptr=FTtop;
    if(FTptr!=NULL){ // If FTtop is NULL then the program should not face abnormal termination
    while(FTptr->next!=NULL)FTptr=FTptr->next;
    FTptr->next=FHTtop;
    }
 }

void KMap::FringeRedundancyEliminator_Horizontal(int i1,int j1,int i2,int j2, int iSize , int jSize){

                           //setting the HEADER pointer to NULL, Indicating an empty NODE
            COtop=NULL;

            //Creating the List of co-ordinates for the requested Map
            for(int r=i1;r<i1+iSize;r++){
                for(int s=j1;s<j1+jSize;s++){
                    insertCoOrdinate(emergeCoOrdinate(r,s));
                    }
                }

            /*Theres no controversy with the first element ,
             so it goes as an entry to the Map table anyways */
            if(FHTtop==NULL){
                pushHEntry(CreateEntry(i1,j1,i2,j2,iSize*2,jSize));
                           }else{
                                FTptr=FHTtop;
                                //Traversing each entry of the Map table
                                while(FTptr!=NULL){
                                    //For each entry , traversing all elements of the entry
                                    for(int r= FTptr->i1;r < FTptr->i1 + FTptr->iSize;r++){
                                        for(int s= FTptr->j1;s < FTptr->j1 + FTptr->jSize; s++){
                                            COptr= COtop;
                                          /*traversing the list of co-ordinates
                                            each element of individual entry of the map table is compared with the whole list of co-ordinates*/
                                            while( COptr!=NULL ){
                                                if(( COptr->i==r)&&( COptr->j==s)){
                                                    COptr->status=true;
                                                }
                                                COptr= COptr->next;
                                                }
                                            }
                                        }
                                       FTptr=FTptr->next;
                                    }

                                COptr= COtop;
                                while( COptr!=NULL){
                                    if( COptr->status==false){ //If any one of the element in the List of co-ordinates is not mapped
                                        pushHEntry(CreateEntry(i1,j1,i2,j2,iSize*2,jSize));//Then add the Map to the Map table
                                        break;
                                        }
                                    COptr= COptr->next;
                                    }
                                }

}

