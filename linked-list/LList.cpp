#include "LList.h"

LList::LNode::LNode ()
{ //we want the pointer to point to no where. which is 0.
  data=0;
  next=NULL;
}

LList::LList ()
{ 
  // this function is intializing first and size.
  this -> first = NULL; 
  this -> size=0;
}

LList::LList (const LList & other)
{// 
  LNode * np = other.first;
  while (np!=NULL)
    {
      this -> InsertLast(np->data);   
      np = np-> next;
    }
}

LList::~LList ()
{ // the destructor, which deletes first as long as the size is greater than 0.
  while (size>0)
    DeleteFirst();
}

LList & LList::operator = (const LList & other)
{ 
  //check for self assignment.
  if(this==&other)
    return * this;
  //clean up, go look at destructor.
  while (size > 0)
    DeleteFirst();

  //copy, the copy constructor.
  for (LNode * np = other.first; np!=NULL; np=np -> next)
    InsertLast(np -> data);
      //return.
	return * this;
}

bool LList::operator == (const LList & other)
{ //
  LNode * np1 = first;
  LNode * np2 =other.first;
  while(np1 !=NULL)
    {
      if (np1 -> data != np2 -> data)
	return false;
      np1=np1 -> next;
      np2=np2 -> next;
    }
  return true;
}

int LList::Size () const
{ // this just returns the size.
	return size;
}

ostream & operator << (ostream & outs, const LList & L)
{
  // display the data in the linked list.
  if(L.size == 0)
    return outs;
  outs << L.first -> data;
  LList:: LNode * np = L.first -> next;
  while (np != NULL)
    {
      outs << ' ' << np -> data;
      np = np -> next;
    }
	return outs;
}

bool LList::InsertFirst (const int & value)
{ //
  LNode * np = new LNode; 
 if(np == NULL)
       return false;
  np -> data = value;
  np -> next = first;
  first = np;
  size ++;
	return true;
}

bool LList::InsertLast (const int & value)
{ //
  if (size ==0)
    return InsertFirst(value);
  LNode * np = new LNode;
  if(np == NULL)
    return false;
  np -> data =value;
  LNode * last = first;
  while (last ->next!= NULL)
    last = last -> next;
  last -> next = np;
  size ++;
}

bool LList ::DeleteFirst ()
{ // This is a stubb; you will be completing this function.

  if(first==NULL)
    return false;
  LNode * np =first;
  first = np -> next;
  size --;
  delete np;
	return true;
}

bool LList::DeleteLast ()
{

  if(first == NULL || size == 0) 
    return false;
  if (size == 1)
    return DeleteFirst(); 
  LNode * secondtolast =first;
  while (secondtolast -> next -> next!=NULL)
    secondtolast = secondtolast -> next;
  delete secondtolast -> next;
  secondtolast -> next = NULL;
  size --;

   return true;
}


