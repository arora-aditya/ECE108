#include "tuple.h"
#include "set.h"
#include "invariant.h"
#include <iostream>
#include <limits.h>   // needed for INT_MIN

int min(int a, int b){
  // Returns the minimum of 2 integers
  return a<b?a:b;
}   

// Set up an error set to be returned as necessary
const Set emptySet(0,(int*)0);
const Set errorSet(-1,(int*)0);

bool Set::isEmpty() const {
  return _numElements == 0;
}

bool Set::isError() const {
  return _numElements == -1;
}
  
int Set::cardinality() const {
  return _numElements;
}

Set Set::union_(const Set& s) const {
  if (_numElements == 0){
    return Set(s);
  }
  if (s._numElements == 0){
    return Set(*this);
  }

  Tuple tuple[s._numElements + _numElements];
  int counter = 0;

  for(int i = 0; i < _numElements; i++) {
    tuple[counter] = _pTuples[i];
    counter++;
  }

  for(int i = 0; i < s._numElements; i++) {
    bool flag = true;
    int j;
    for(j = 0; j < counter; j++) {
      if(tuple[j] == s._pTuples[i]){
        flag = false;
        break;
      }
    }

    if(flag) {
      tuple[counter] = s._pTuples[i];
      counter++;
    }
  }
  return Set(counter, tuple); 
}

Set Set::intersection(const Set& s) const {
	if (_numElements == 0 || s._numElements == 0){
    return emptySet;
  }
  Tuple tuple[s._numElements + _numElements];
  int counter = 0;
  for(int i = 0; i < _numElements; i++) {
    for(int j = 0; j < s._numElements; j++) {
      if(_pTuples[i] == s._pTuples[j]) {
        tuple[counter] = _pTuples[i];
        counter++;
        break;
      }
    }
  }
  return Set(counter, tuple);  
}

Set Set::difference(const Set& s) const {
  // return emptySet;
  if (_numElements == 0){
    return emptySet;
  }
  else if (s._numElements == 0){
    return Set(s._numElements, s._pTuples);
  }
  Tuple *  tuple = new Tuple[_numElements];
  int counter = 0;
  for(int i = 0; i < _numElements; i++) {
    bool flag = true;
    for(int j = 0; j < s._numElements; j++) {
      if(_pTuples[i] == s._pTuples[j]) {
        flag = false;
        break;
      }
    }
    if(flag){
      tuple[counter] = _pTuples[i];
      counter++;
    }
  }
	if(counter == 0){
		return emptySet;
	}
  // std::cout << "out of there" << std::endl;
  return Set(counter, tuple);
	// Set m =  &k;
	// return m;
	// std::cout << k << std::endl;
	 
}

Set Set::select(predicate* p) const {
  int counter = 0;
  Tuple Tuples[_numElements+1];
  for(int i = 0; i < _numElements; i++){
    if((*p)(_pTuples[i]) == true) {
      Tuples[counter] = _pTuples[i];
      counter++;
    }
  }
  return Set(counter, Tuples); 
}

Set Set::project(const int numItems, const int items[]) const {
	// return emptySet;
  // std::cout << "reached project" << std::endl;
  if(numItems == 0){
		Tuple k[1];
		return Set(1,k);
	}


  int _minTupleSize = INT_MAX;
	bool flag = true;
  for(int i = 0; i < _numElements; i++) {
		flag = false;
		std::cout << _pTuples[i].size() << "-";
    _minTupleSize = min(_minTupleSize, _pTuples[i].size());
	}
	std::cout << flag << std::endl;
	if(flag){
		_minTupleSize = - INT_MAX;
	}
  for(int i = 0; i <  numItems; i++) {
    if(items[i] > _minTupleSize) {
      return Set(-1, (int*)0);
    }
  }
	// std::cout << "_minTupleSize: " << _minTupleSize << std::endl; 
	// std::cout << "reached line" << std::endl;
  Tuple *  tup = new Tuple[_numElements];
  for(int i = 0; i < _numElements; i++) {
		// std::cout<<i+1<<'\t';
		if(_pTuples[i] == _pTuples[i]){
			*(tup+i) = (_pTuples[i].project(numItems, items));
		}
		else{
			*(tup+i) = _pTuples[i];
		}
	}

	// std::cout<<"reached almost";
  return Set(_numElements, tup);
}

Set Set::cartesian(const Set& s) const {
  if (_numElements == 0 || s._numElements == 0){
    return emptySet;
  }
  Tuple * tuple = new Tuple[_numElements * s._numElements];
  int counter = 0;
  for(int i = 0; i < _numElements; i++) {
    for(int j = 0; j < s._numElements; j++) {
      int data[_pTuples[i].size() + s._pTuples[j].size()];
      Tuple t4 = _pTuples[i] + s._pTuples[j];
      tuple[counter] = t4;
      counter++;
    }
  }

  const int size = _numElements * s._numElements;
  Tuple tu[size];
  for(int i = 0; i < size; i++){
    tu[i] = tuple[i];
  }
  if(tuple){
    delete[] tuple;
  }
  return Set(_numElements * s._numElements, tu);
}

void Set::operator=(const Set& s) {
	_numElements = s._numElements;
  _pTuples = new Tuple[s._numElements+1];
  _tupleArraySize = s._tupleArraySize;
  for(int i = 0; i < _numElements; i++){
    _pTuples[i] = s._pTuples[i];
  }
}

Set Set::operator()(const int item) const {
  int k[] = {item};
	Set m =  this->project(1, k);
	std::cout << m << "()" << std::endl;
  return errorSet;
}

Set::Set() {
	_numElements = 0;
  _tupleArraySize = 0;
  Tuple* _pTuples = NULL;
}

Set::Set(const Set& s) {
	_numElements = s._numElements;
  _pTuples = new Tuple[s._numElements+1];
  _tupleArraySize = s._tupleArraySize;
  for(int i = 0; i < _numElements; i++){
    _pTuples[i] = s._pTuples[i];
  }
  // std::cout << _pTuples << *this << std::endl;
}

Set::Set(const int numElements, const int data[]) {
	if(numElements == -1){
    _numElements = -1;
    return;
  }
  if (numElements <= 0){
    return;
  }
  /*if (data != data){
 *     return;
 *       }*/
  int copy[numElements];
  int size = 1;
  copy[0] = data[0];
  for(int i = 0; i < numElements; i++) {
    bool flag = true;
    for(int j = 0; j < size; j++){
      if(copy[j] == data[i]){
        flag = false;
        break;
      }
    }
    if(flag){
      copy[size] = data[i];
      size++;
    }
  }
  _pTuples = new Tuple[size+1];
  _numElements = size;
  for(int i = 0; i < size; i++){
    _pTuples[i] = copy[i] ;
  }
  // std::cout << _pTuples << *this << std::endl;
}

Set::Set(const int numElements, const Tuple tuples[]) {
	if(numElements == -1){
    _numElements = -1;
    return;
  }
  if (numElements <= 0){
    return;
  }
  Tuple copy[numElements];
  int size = 1;
  copy[0] = tuples[0];
  for(int i = 0; i < numElements; i++) {
    bool flag = true;
    for(int j = 0; j < size; j++){
      if(copy[j] == tuples[i]){
        flag = false;
        break;
      }
    }
    if(flag){
      copy[size] = tuples[i];
      size++;
    }
  }
  _numElements = size;
  _pTuples = new Tuple[size+1];
  int i, counter=0;
  for(i = 0; i < numElements; i++){
		if(copy[i] == copy[i]){
			_pTuples[counter] = copy[i];
			counter += 1;
		}
  }
	_numElements = counter;
}

Set::~Set() {
	/*if(_pTuples != NULL){
    std::cout << *this << "-" << _pTuples <<std::endl;
    delete[] _pTuples;
  }*/
  _numElements = -1;
  _tupleArraySize = 0;
	}

std::ostream& operator<<(std::ostream& os, const Set& s) {
	if(s.isError()){
    os << "{ERRORSET}";
    return os;
  }
  os << "{";
  if(s._numElements != 0){
    for(int i = 0; i < s._numElements; i++){
      os << s._pTuples[i];
      if(i != s._numElements-1){
        os << ",";
      }
    }
  }
  os << "}";
  return os;
}
