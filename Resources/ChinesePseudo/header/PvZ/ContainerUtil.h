/*
 * ContainerUtil.h
 *
 *  Created on: 2019-4-8
 *      Author: zhousen
 */

#ifndef CONTAINERUTIL_H_
#define CONTAINERUTIL_H_

template<class T>
class FuncTrait
{
public:
    typedef bool (*PredicateFunc)(T, T);
};

class ContainerUtil
{
public:
    template<class T>
    static int FindIndexInContainer(std::vector<T> list, T compare, typename FuncTrait<T>::PredicateFunc func) {
        for(int i = 0; i < list.size(); ++i){
            if (func(list[i], compare)){
                return i;
            }
        }
        return -1;
    }

    template<class T>
    static bool IsInContainer(std::vector<T> list, T value) {
#if true
    	for(int i = 0; i < list.size(); ++i){
			if (value == list[i]){
				return true;
			}
		}
		return false;
#else
        if (list.empty()) return false;

        aauto iter = std::find_if(list.begin(), list.end(), [value](const T& compare_value){
            return value == compare_value;
        });

        return iter != list.end();
#endif
    }

    template<class T>
    static std::vector<T> SubtractContainer(std::vector<T> list1, std::vector<T> list2) {
        std::vector<T> listRet;
        listRet.assign(list1.begin(), list1.end());
        for(auto& item : list2) {
            typename std::vector<T>::iterator iter = find(listRet.begin(), listRet.end(), item);
            if (iter != listRet.end()) {
                listRet.erase(iter);
            }
        }
        return listRet;
    }

    template<class T>
    static bool FillContainer(std::vector<T>& list, T* ptr, int size) {
        for(int i = 0; i < size; ++i) {
            list.push_back(*(ptr + i));
        }
    }
};


#endif /* CONTAINERUTIL_H_ */
