# ifndef LINKED_LIST_COLLECTION_H
# define LINKED_LIST_COLLECTION_H

# include <vector>
# include <algorithm>
# include <iostream>
# include "collection.h"


template < typename K , typename V >
class LinkedListCollection : public Collection <K ,V >
{
 public :

// create an empty linked list
LinkedListCollection ();

// copy a linked list
LinkedListCollection (const LinkedListCollection <K ,V >& rhs );

// assign a linked list
LinkedListCollection <K ,V >& operator=(const LinkedListCollection <K ,V >& rhs );

// delete a linked list
 ~ LinkedListCollection ();

// insert a key - value pair into the collection
void insert(const K& key , const V& val);

// remove a key - value pair from the collection
void remove(const K& key);

// find the value associated with the key
bool find(const K& key , V& val) const ;

// find the keys associated with the range
void find(const K& k1 , const K& k2 , std :: vector <K>& keys) const ;

// return all keys in the collection
void keys(std :: vector <K >& keys) const ;

// return collection keys in sorted order
void sort(std :: vector <K >& keys) const ;

// return the number of keys in collection
int size() const ;

// in place sorting
void insertion_sort();
void merge_sort();
void quick_sort();

  private:
// linked list node structure
 struct Node {
  K key ;
  V value ;
  Node* next ;
 };

 Node* head ; // pointer to first list node
 Node* tail ; // pointer to last list node
 int length ; // number of linked list nodes in list

 // helper to delete linked list
 void make_empty();

 // merge sort helper ( see course notes for details )
 Node* merge_sort(Node* left , int len);

 // quick sort helper ( see course notes for details )
 Node* quick_sort(Node* start , int len);
};

template<typename K, typename V>
void LinkedListCollection<K, V>::make_empty()
{
 Node* cur=head;
 while(cur!= nullptr)
 {
  Node* temp=cur->next;
  delete cur;
  cur=temp;
 }
 head=nullptr;

}

template<typename K, typename V>
LinkedListCollection<K, V>::LinkedListCollection()
{
 head=nullptr;
 tail=nullptr;
 length=0;
}

template<typename K, typename V>
LinkedListCollection<K, V>::
LinkedListCollection(const LinkedListCollection<K, V>& rhs)
{
 Node* cur=rhs.head;
 while(cur != nullptr)
 {
  this->insert(cur->key, cur->value);
  cur=cur->next;
 }
}

template<typename K, typename V>
LinkedListCollection<K, V>& LinkedListCollection<K, V>
::operator=(const LinkedListCollection<K, V>& rhs)
{
 Node* temp=head;
 if(this == &rhs)
   return *this;
 while(temp->next!= nullptr)
 {
  head=head->next;
  delete temp;
  temp=head;
  length--;
 }
 temp=rhs.head;
 while(temp != nullptr)
 {
  this->insert(temp->key, temp->value);
  temp=temp->next;
 }
 return *this;
}

template<typename K, typename V>
LinkedListCollection<K, V>::~LinkedListCollection()
{
 std :: make_empty();
}

template<typename K, typename V>
void LinkedListCollection<K, V>::insert(const K& key, const V& val)
{
 Node* ins=new Node;
 ins->key=key;
 ins->value=val;

 if(length == 0)
 {
  head=ins;
  tail=ins;
  ins->next=nullptr;
  this->length++;
 }
 else
 {
  tail->next=ins;
  ins->next=nullptr;
  tail=ins;
  length++;
 }
}

template<typename K, typename V>
void LinkedListCollection<K, V>::remove(const K& key)
{
 Node* prev=new Node;
 Node* cur=head;
 while(cur != nullptr)
 {
  if(cur->key == key)
  {
   prev->next=cur->next;
   delete cur;
   this->length--;
  }
  else
  {
   prev=cur;
   cur=cur->next;
  }
 }
}

template<typename K, typename V>
bool LinkedListCollection<K, V>::find(const K& key, V& val) const
{
 Node* temp=head;
 while(temp != nullptr)
 {
  if(temp->key == key)
  {
   val=temp->value;
   return true;
  }
  else
    temp=temp->next;
 }
  return false;
}

template<typename K, typename V>
void LinkedListCollection<K, V>::find(const K& k1, const K& k2, std::vector<K>& keys) const
{
 Node* temp=head;
 while(temp != nullptr)
 {
  if(temp->key >= k1 && temp->key <= k2)
   keys.push_back(temp->key);
  temp=temp->next;
 }
}

template<typename K, typename V>
void LinkedListCollection<K, V>::keys(std::vector<K>& keys) const
{
 Node* cur=head;
 while(cur != nullptr)
 {
  keys.push_back(cur->key);
  cur=cur->next;
 }
}

template < typename K , typename V >
void LinkedListCollection <K ,V >:: sort(std :: vector <K >& keys ) const
{
 Node* ptr=head;
 while(ptr != nullptr) 
 {
  keys.push_back(ptr->key);
  ptr=ptr->next;
 }
 std :: sort(keys.begin() , keys.end());
}

template < typename K , typename V >
int LinkedListCollection<K,V> :: size() const{
  return length;
}

template<typename K, typename V>
void LinkedListCollection<K, V>::insertion_sort()
{
 Node* cur=head;
 Node* temp;
 for(int i=1;i<length;++i)
 {
  bool TF=false;
  temp=head;
  while(!TF && temp != cur->next)
  {
   TF=false;
   if(cur->next->key < head->key)
   {
    Node* nex=cur->next;
    cur->next=cur->next->next;
    nex->next=head;
    head=nex;
    TF=true;
   }
   else if(cur->next->key < sortStart->next->key)
   {
    Node* nex=cur->next;
    cur->next=cur->next->next;
    nex->next=sortStart->next;
    temp->next=nex;
    TF=true;
   }

   else
    temp=temp->next;
  }
    if(!TF) {
      cur=cur->next;
	}
  }
}

template<typename K, typename V>
typename LinkedListCollection<K, V>::Node*
LinkedListCollection<K, V>::merge_sort(Node* left, int len)
{
 if(length == 1) {
  return left;
 }

 Node* temp=left;
 Node* right;
 Node* cur;
 int mid=len/2;
 int count=0;
 while(count < mid-1)
 {
  temp=temp->next;
  count++;
 }
 right=temp->next;
 left=merge_sort(left, mid);
 right=merge_sort(right, len-mid);
 
 if left->key < right->key)
 {
  cur=left;
  left=left->next;
  cur->next=nullptr;
 }
 else
 {
  cur=right;
  right=right->next;
  cur->next=nullptr;
 }
 temp=cur;
 
 for(int i=0;i<len-1;++i)
 {
  if(left == nullptr)
  {
   temp->next=right;
   right=right->next;
   temp->next->next=nullptr;
   temp=temp->next;
  }
  else if(right == nullptr)
  {
   temp->next = left;
   left = left->next;
   temp->next->next = nullptr;
   temp=temp->next;
  }
  else if(left->key < right->key)
  {
   temp->next=left;
   left=left->next;
   temp->next->next=nullptr;
   temp=temp->next;
  }
  else
  {
   temp->next=right;
   right=right->next;
   temp->next->next = nullptr;
   temp=temp->next;
  }
 }

 return cur;
}

template<typename K, typename V>
void LinkedListCollection<K, V>::merge_sort()
{
 head merge_sort(this->head, this->length);
 tail=head;
 while(tail->next != nullptr){
  tail=tail->next;
 }
}

template<typename K, typename V>
typename LinkedListCollection<K, V>::Node*
LinkedListCollection<K, V>::quick_sort(Node* start, int len)
{
 int len1=0;
 int len2=0;
 Node* cur=start->next;
 Node* left=new Node;
 Node* right=new Node;
 Node* lend;
 Node* rend;
 if(len <= 1){
  return start;
 } 
 
 if(len == 2)
 {
  if(start->key > start->next->key)
  {
   Node* temp=start;
   start=start->next;
   start->next=temp;
   return start;
  }
 }

 while(cur != nullptr)
 {
  if(cur->key < start->key && left == nullptr){
   left=cur;
  }
  if(cur->key >= start->key && right == nullptr){
   right=cur;
  }
  cur=cur->next;
 }

 cur=start->next;
 start->next = nullptr;
 lend=left;
 rend=right;

 while(cur != nullptr)
 {
  if(left != nullptr)
  {
   if(cur->key < start->key && cur != left)
   {
    lend->next = cur;
    lend=lend->next;
   }
  }
   if(right != nullptr)
   {
    if(cur->key >= start->key && cur != right)
    {
     rend->next = cur;
     rend=rend->next;
    }
   }
  cur=cur->next;
 }

 if(lend != nullptr) {
  lend->next = nullptr;
 }
 if(rend != nullptr){
   rend->next = nullptr;
 }
 cur=left;

 if(left != nullptr)
 {
  while(cur != nullptr)
  {
   len1++;
   cur=cur->next;
  }
 }

 cur=right;
 if(right != nullptr)
 {
  while(cur != nullptr)
  {
   len2++;
   cur=cur->next;
  }
 }

 if(left != nullptr){
  left=quick_sort(left, len1);
 }
 if(right != nullptr){
  right=quick_sort(right, len2);
 }

 if(left != nullptr)
 {
  cur=left;
  while(cur->next != nullptr){
   cur = cur->next;
  }
  lend=cur;
  lend->next = start;
  start->next = right;
  return left;
 }

 if(left == nullptr)
 {
  start->next = right;
  return start;
 }
}

template<typename K, typename V>
void LinkedListCollection<K, V>::quick_sort()
{
 head=quick_sort(head, length);
 tail=head;
 while(tail->next != nullptr){
  tail=tail->next;
 }
}

#endif