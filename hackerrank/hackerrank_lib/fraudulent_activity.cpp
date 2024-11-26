//
// Created by vozak on 2024. 10. 29..
//
#include <bits/stdc++.h>
#include "fradulent_activity.h"

using namespace std;

pair<int, int> getMedians(const multiset<int> &m) {
    auto it = m.begin();
    advance(it, m.size() / 2 - 1);

    const int median = *it;
    advance(it, 1);
    const int median2 = *it;
    return {median, median2};
}

int getMedian(const multiset<int> &m) {
    auto it = m.begin();
    advance(it, m.size() / 2);

    return *it;
}

bool isBetween(const int min, const int max, const int num) {
    return min < num && num < max;
}

class Expenditure {
public:
    virtual ~Expenditure() = default;

    int countWarning() {
        int count = 0;
        setup();

        while (currentIndex < expenditure.size()) {
            if (limit <= expenditure[currentIndex]) {
                count++;
            }
            updateState();
        }

        return count;
    }

    explicit Expenditure(const vector<int> &expenditure) : expenditure(expenditure) {
    }

protected:
    virtual void updateState() = 0;

    virtual void setup() = 0;

    vector<int> expenditure;
    int limit{};
    int currentIndex{};
};

class Expenditure1 final : public Expenditure {
protected:
    void setup() override {
        median = expenditure[0];
        currentIndex = 1;
        limit = median * 2;
    }

    void updateState() override {
        median = expenditure[currentIndex];
        limit = median * 2;
        currentIndex++;
    }

public:
    explicit Expenditure1(const vector<int> &expenditure) : Expenditure(expenditure), median(expenditure[0]) {
    }

private:
    int median;
};

class Expenditure2 final : public Expenditure {
protected:
    void setup() override {
        medians.emplace(expenditure[0]);
        medians.emplace(expenditure[1]);
        limit = expenditure[0] + expenditure[1];
        currentIndex = 2;
    }

    void updateState() override {
        medians.pop();
        medians.emplace(expenditure[currentIndex]);
        limit = expenditure[currentIndex] + expenditure[currentIndex - 1];
        currentIndex++;
    }

public:
    explicit Expenditure2(const vector<int> &expenditure) : Expenditure(expenditure) {
    }

private:
    queue<int> medians;
};

class ExpenditureOdd : public Expenditure {
public:
    explicit ExpenditureOdd(int d, const vector<int> &expenditure) : Expenditure(expenditure), d(d) {
    }

private:
    int median;
    int d;
    multiset<int> smaller = multiset<int>();
    multiset<int> greater = multiset<int>();

    void setup() override {
        multiset<int> frame;

        for (int i = 0; i < d; i++) {
            frame.insert({expenditure[i]});
        }

        median = getMedian(frame);
        limit = 2 * median;
        currentIndex = d;

        auto it = frame.begin();
        int i = 0;
        const int lastSmallIndex = d / 2;
        for (int i = 0; i < lastSmallIndex; i++) {
            smaller.insert(*it);
            it++;
        }
        it++;
        while (it != frame.end()) {
            greater.insert(*it);
            it++;
        }
    }

    void updateState() override {
        const int newElement = expenditure[currentIndex];
        const int deletedElement = expenditure[currentIndex - d];
        currentIndex++;


        if (deletedElement == newElement) {
            return;
        }

        const bool deleteSmaller = deletedElement < median;
        const bool addSmaller = newElement < median;
        const bool addLarger = newElement > median;
        const bool deleteLarger = deletedElement > median;

        if (deleteSmaller) {
            smaller.extract(deletedElement);
            if (addLarger) {
                smaller.insert(median);
                int smallestLargeNumber = *greater.begin();
                if (newElement < smallestLargeNumber) {
                    median = newElement;
                } else {
                    median = smallestLargeNumber;
                    greater.extract(greater.begin());
                    greater.insert(newElement);
                }
            } else {
                smaller.insert(newElement);
            }
        } else if (deleteLarger) {
            greater.extract(deletedElement);
            if (addSmaller) {
                greater.insert(median);
                int largestSmallNumber = *smaller.rbegin();
                if (newElement > largestSmallNumber) {
                    median = newElement;
                } else {
                    median = largestSmallNumber;
                    smaller.extract(median);
                    smaller.insert(newElement);
                }
            } else {
                greater.insert(newElement);
            }
        } else //if (deleteMed1)
        {
            if (addSmaller) {
                int largestSmallNumber = *smaller.rbegin();
                if (newElement > largestSmallNumber) {
                    median = newElement;
                } else {
                    median = largestSmallNumber;
                    smaller.extract(median);
                    smaller.insert(newElement);
                }
            } else {
                int smallestLargeNumber = *greater.begin();
                if (newElement < smallestLargeNumber) {
                    median = newElement;
                } else {
                    median = smallestLargeNumber;
                    greater.extract(greater.begin());
                    greater.insert(newElement);
                }
            }
        }
        limit = median * 2;
    }
};

class ExpenditureEven : public Expenditure {
public:
    explicit ExpenditureEven(int d, const vector<int> &expenditure) : Expenditure(expenditure), d(d) {
    }

private:
    int median;
    int median2;
    int d;
    multiset<int> smaller = multiset<int>();
    multiset<int> greater = multiset<int>();

    void setup() override {
        multiset<int> frame;

        for (int i = 0; i < d; i++) {
            frame.insert({expenditure[i]});
        }
        tie(median, median2) = getMedians(frame);
        limit = median + median2;
        currentIndex = d;

        auto it = frame.begin();
        const int lastSmallIndex = d / 2 - 1;
        for (int i = 0; i < lastSmallIndex; i++) {
            smaller.insert(*it);
            it++;
        }
        advance(it, 2);
        while (it != frame.end()) {
            greater.insert(*it);
            it++;
        }
    }

    void updateState() override {
        const int newElement = expenditure[currentIndex];
        const int deletedElement = expenditure[currentIndex - d];
        currentIndex++;

        if (deletedElement == newElement) {
            return;
        }

        const bool deleteLarger = deletedElement > median2;
        const bool addLarger = newElement > median2;
        const bool deleteSmaller = deletedElement < median;
        const bool addSmaller = newElement < median;
        const bool addMed1 = newElement == median;
        const bool addMed2 = newElement == median2;
        const bool deleteMed1 = deletedElement == median;
        const bool deleteMed2 = deletedElement == median2;
        const bool addBetweenMeds = isBetween(median, median2, newElement);

        if (deleteSmaller) {
            smaller.extract(deletedElement);
            if (addSmaller || addMed1) {
                smaller.insert(newElement);
            } else if (addBetweenMeds || addMed2) {
                smaller.insert(median);
                median = newElement;
            } else // if (addLarger)
            {
                smaller.insert(median);
                median = median2;
                int smallestLargeNumber = *greater.begin();
                if (newElement < smallestLargeNumber) {
                    median2 = newElement;
                } else {
                    median2 = smallestLargeNumber;
                    greater.extract(median2);
                    greater.insert(newElement);
                }
            }
        } else if (deleteLarger) {
            greater.extract(deletedElement);
            if (addLarger || addMed2) {
                greater.insert(newElement);
            } else if (addBetweenMeds || addMed1) {
                greater.insert(median2);
                median2 = newElement;
            } else // if (addSmaller)
            {
                smaller.insert(newElement);
                greater.insert(median2);
                median2 = median;
                median = *(smaller.rbegin());
                smaller.extract(median);
            }
        } else if (deleteMed1) {
            if (addSmaller) {
                int biggestSmallNumber = *smaller.rbegin();
                if (newElement > biggestSmallNumber) {
                    median = newElement;
                } else {
                    median = biggestSmallNumber;
                    smaller.extract(median);
                    smaller.insert(newElement);
                }
            } else if (addBetweenMeds || addMed2) {
                median = newElement;
            } else //if (addLarger)
            {
                median = median2;
                int smallestLargeNumber = *greater.begin();
                if (newElement < smallestLargeNumber) {
                    median2 = newElement;
                } else {
                    median2 = smallestLargeNumber;
                    greater.extract(median2);
                    greater.insert(newElement);
                }
            }
        } else if (deleteMed2) {
            if (addSmaller) {
                smaller.insert(newElement);
                median2 = median;
                median = *smaller.rbegin();
                smaller.extract(median);
            } else if (addMed1) {
                median2 = median;
            } else if (addBetweenMeds) {
                median2 = newElement;
            } else // if (addLarger)
            {
                int smallestLargeNumber = *greater.begin();
                if (newElement < smallestLargeNumber) {
                    median2 = newElement;
                } else {
                    median2 = smallestLargeNumber;
                    greater.extract(median2);
                    greater.insert(newElement);
                }
            }
        }

        limit = median + median2;
    }
};

class ExpenditureFactory {
public:
    static Expenditure* fillInstance(int d, const vector<int> &expenditure) {
        Expenditure* exp;
        if (d == 1) {
            exp = new Expenditure1(expenditure);
        } else if (d == 2) {
            exp = new Expenditure2(expenditure);
        } else if (d % 2 == 0) {
            exp = new ExpenditureEven(d, expenditure);
        } else {
            exp = new ExpenditureOdd(d, expenditure);
        }

        return exp;
    }

    ExpenditureFactory() = delete;
};


int activityNotifications(vector<int> expenditure, int d) {
    if (d >= expenditure.size()) {
        return 0;
    }

    Expenditure *exp = ExpenditureFactory::fillInstance(d, expenditure);

    return exp->countWarning();
}


