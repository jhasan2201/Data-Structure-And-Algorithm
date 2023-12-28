#include "iostream"
#include "vector"
#include "algorithm"

using namespace std;


//1. Fractional Knapsack

bool cmp1(pair<int,int> &pair1,pair<int,int> &pair2){
    double valuePerWei1=(double )pair1.first/pair1.second;
    double valuePerWei2=(double )pair2.first/pair2.second;
    return valuePerWei1>valuePerWei2;
}

double fractionalKnapsack(vector<int> &value,vector<int> &weight,int capacity){
    vector<pair<int,int>> list;
    for (int i = 0; i < value.size(); ++i) {
        list.push_back({value[i],weight[i]});
    }
    sort(list.begin(), list.end(), cmp1);

    double wei=(double )capacity;
    double money=0;

    for (auto item:list) {
        double portion=min(1.0,wei/item.second);
        wei-= portion*item.second;
        money+= portion*item.first;
    }
    return money;
}

//2. Thieves in warehouse

struct Product{
    string name;
    int value;
    int weight;
    Product(string name,int value,int weight){
        this->name=name;
        this->weight=weight;
        this->value=value;
    }
};

bool cpm2(Product &p1,Product &p2){
    double valPerWei1=(double )p1.value/p1.weight;
    double valPerWei2=(double )p2.value/p2.weight;
    return valPerWei1>valPerWei2;
}

double thievesInWareHouse(vector<string> &itemName,vector<int> &value,vector<int> &weight,vector<int> &thCapacity){

    vector<Product> list;
    for (int i = 0; i < itemName.size(); ++i) {
        list.push_back(Product(itemName[i],value[i],weight[i]));
    }

    sort(list.begin(), list.end(),cpm2);

    int j=1;
    for (auto thiefCap:thCapacity) {
        double capcity=thiefCap;
        double money=0;
        int i=0;
        for (auto item:list) {
            double portion=min(1.0,capcity/item.weight);
            cout<<item.name<<" : "<<portion*item.weight<<" Kg "<<portion*item.value<<" tk"<<endl;
            capcity-= portion*item.weight;
            list[i].weight -=portion*item.weight;
            money+= portion*item.value;
            list[i].value -=portion*item.value;
            i++;
        }
        cout<<"Thief"<<j<< " Profit: "<<money<<endl<<endl;
        j++;
    }
}


//3. Maximize your marks
//struct Ques{
//    int no;
//    int marks;
//    int time;
//    Ques(int no,int marks,int time){
//        this->time=time;
//        this->marks=marks;
//        this->no=no;
//    }
//
//};
//bool cmp4(Ques &q1,Ques &q2){
//    double marksPerMin1=(double )q1.marks/q1.time;
//    double marksPerMin2=(double )q2.marks/q2.time;
//    return marksPerMin1>marksPerMin2;
//}
//double maxiMumMarks(vector<int> &marks,vector<int> &time,int totalTime,int totalMarks){
//    vector<Ques> list;
//    for (int i = 0; i < marks.size(); ++i) {
//        list.push_back(Ques(i+1,marks[i],time[i]));
//    }
//    sort(list.begin(), list.end(),cmp4);
//
//    double marksObtain=0;
//    double timeRemaining=totalTime;
//
//    for (auto q:list) {
//        if(marksObtain>totalMarks || timeRemaining<=0){
//            break;
//        }
//        double portion=min(1.0,timeRemaining/q.time);
//        timeRemaining -= portion*q.time;
//        marksObtain += portion*q.marks;
//        cout<<"Ques "<<q.no<<" :"<<portion*100<<"% "<<portion*q.marks<<endl;
//    }
//
//    return marksObtain;
//
//}

//4. Activity Selection Problem

bool cmp3(pair<int,int> &p1,pair<int,int> &p2){
    return p1.second<p2.second;
}

int activitySelection(vector<int> &start,vector<int> &end){
    vector<pair<int,int>> time;
    for (int i = 0; i < start.size(); ++i) {
        time.push_back({start[i],end[i]});
    }
    sort(time.begin(), time.end(),cmp3);

    int endTime=time[0].second;
    vector<pair<int,int>> done;
    done.push_back(time[0]);
    for (int i = 1; i < time.size(); ++i) {
        if(time[i].first >= endTime){
            endTime=time[i].second;
            done.push_back(time[i]);
        }
    }

    for (auto x:done) {
        cout<<x.first<<" --> "<<x.second<<endl;
    }
    cout<<endl;

    return done.size();
}


//5. Greedy Coin Change

int coinChange(vector<int> &coins,int target){
    sort(coins.begin(), coins.end(),greater<int>());

    int ans=0;
    for (auto co:coins) {
        int noOfCoin=target/co;
        ans+= noOfCoin;
        target -= co*noOfCoin;
    }
    return ans;
}

//6. Finding Minimum Stops  [Unsolved]
//7. Determine the smallest set of unit-length closed intervals  [Unsolved]
//8. Huffman Encoding
//9. Max Meeting in One Room
//10. Shop candy problem
//11. Reverse word in a given string
//12. Survive on Island
//13. Chocolate distribution problem
//14. Min cost of Ropes
//15. Job sequencing problem
//16. Activity selection in hall room (alternative ques)

bool cmp5(pair<int,int> &event1,pair<int,int> &event2){
    return event1.second<event2.second;
}

int peopleNeedActivity(vector<int> &start,vector<int> &end){
    vector<pair<int,int>> workList;
    for (int i = 0; i < start.size(); ++i) {
        workList.push_back({start[i],end[i]});
    }
    sort(workList.begin(), workList.end(),cmp5);

    vector<vector<pair<int,int>>> ans;
    while (!workList.empty()){
        vector<pair<int,int>> people;
        people.push_back(workList[0]);
        int endtime=workList[0].second;
        workList.erase(workList.begin());
        vector<pair<int,int>>::iterator it;
        for (it=workList.begin();it<=workList.end();it++){
            if(people.size()>=3){
                break;
            }
            if(it->first>=endtime){
                endtime=it->second;
                people.push_back(*it);
                workList.erase(it);
            }
        }
        ans.push_back(people);
    }

    for (auto x:ans) {
        cout<<"people:"<<endl;
        for (auto y:x) {
            cout<<y.first<<" "<<y.second<<endl;
        }
    }
    cout<<endl;
    return ans.size();
}


//17. Multiple Knapsack

int multipleKanpsack(vector<int> &weight,vector<int> &value,int capacity){
    vector<Product> list;
    for (int i = 0; i < weight.size(); ++i) {
        list.push_back(Product(to_string(i+1),value[i],weight[i]));
    }
    sort(list.begin(), list.end(),cpm2);
    vector<vector<Product>> ans;

    while (!list.empty()){
        double cap=capacity;
        double money=0;
        vector<Product> thief;
        for (auto item:list) {
            double portion=min(1.0,cap/item.weight);

            cap -= portion*item.weight;
            money +=portion*item.value;

            item.weight -=portion*item.weight;
            item.value -=portion*item.value;

            thief.push_back(Product(item.name,portion*item.value,portion*item.weight));

            if(portion==1){
                list.erase(list.begin());
            }
        }
        ans.push_back(thief);
    }

    for (auto x:ans) {
        cout<<"Thief"<<endl;
        for (auto y:x) {
            cout<<"Item "<< y.name<<" "<< y.weight <<" Kg "<<y.value<<" tk "<<endl;
        }
    }


    return ans.size();

}


int main(){
    int choice;
    cout<<"Choice:";
    cin>>choice;
    while (choice){
        switch (choice) {
            case 1:{
                vector<int> value={120,280,120,100};
                vector<int> wei={20,40,24,10};
                cout<<fractionalKnapsack(value,wei,60)<<endl;
                break;

            }
            case 2:{
                vector<string> product_name={"silver-dust","gold-dust","salt","sugar"};
                vector<int> value={300,2000,80,89};
                vector<int> weight={4,8,10,10};
                vector<int> thiCapacity={15,15};
                thievesInWareHouse(product_name,value,weight,thiCapacity);
                break;
            }

            case 3:{
                vector<int> marks={20,20,30,30,20};
                vector<int> time={10,5,5,6,40};
                //cout<<maxiMumMarks(marks,time,120,20)<<endl;
                break;
            }

            case 4:{
                vector<int> start={5,3,6,3,1,8,8,12,2,0,5};
                vector<int> end={7,5,10,8,4,12,11,14,13,6,9};
                cout<<activitySelection(start,end)<<endl;
                break;
            }
            case 5:{
                vector<int> coins={10,1,25,5};
                cout<<coinChange(coins,173)<<" coins \n";
                break;
            }

            case 16:{
                vector<int> start={11,2,9,2,1,3,1,4,10};
                vector<int> end={13,4,15,10,3,7,5,8,14};
                cout<<peopleNeedActivity(start,end)<<endl;
                break;
            }
            case 17:{
                vector<int> weight={10,15,12,8};
                vector<int> value={200,150,360,100};
                cout<<multipleKanpsack(weight,value,8)<<endl;
                break;
            }
        }
        cout<<"Choice:";
        cin>>choice;
    }
}