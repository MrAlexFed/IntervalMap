#pragma once

#include <iostream>
#include <list>
#include <functional>
#include <memory>
#include <utility>
namespace fadeev {

    template<typename Key, typename Value>
    class IntervalMap {
    public:
        IntervalMap() = default;

        IntervalMap(const IntervalMap&) = delete;
        IntervalMap(IntervalMap&&) = delete;
        IntervalMap& operator=(const IntervalMap&) = delete;
        IntervalMap& operator=(IntervalMap&&) = delete;
        ~IntervalMap() = default;

        class Intervals;
        Intervals& operator[](const Key& key);



        class Intervals {
        public:
            void insert(const Value& left, const Value& right);
            const std::list<std::pair<Value, Value>>& data() const { return data_; }

        private:
            std::list<std::pair<Value, Value>> data_;
        };

    private:
        struct IMNode {
            Key key;
            Intervals intervals;

            std::unique_ptr<IMNode> left;
            std::unique_ptr<IMNode> right;
        };

        std::unique_ptr<IMNode> root_;
        size_t size_ = 0;

    public:

        friend std::ostream& operator<<(std::ostream& output, const IntervalMap::IMNode& node) {
            output << '{' << node.key << " : " ;
            const auto& intervalData = node.intervals.data();
            for (auto it = intervalData.begin(); it != intervalData.end(); ++it) {
                output << '(' << it->first << ", " << it->second << ')';

                auto itNext = it;
                itNext++;
                if (itNext != intervalData.end())
                    output << ", ";
            }
            output << '}';
            return output;
        }

        friend std::ostream& operator<<(std::ostream& output, const IntervalMap& mp) {
            int count = 0;
            std::function<void(const std::unique_ptr<IntervalMap::IMNode>& node)> traverse = [&](const std::unique_ptr<IntervalMap::IMNode>& node) {
                if (node) {
                    traverse(node->left);

                    output << *node.get();
                    count++;
                    if (count < mp.size_)
                        output << ", ";

                    traverse(node->right);
                }
            };



            output << '[';
            traverse(mp.root_);
            output << ']';
            return output;
        }
    };

} // namespace fadeev

template<typename Key, typename Value>
void fadeev::IntervalMap<Key, Value>::Intervals::insert(const Value& left, const Value& right) {
    if (left >= right)
        throw std::runtime_error("Wrong interval borders");



    std::pair<Value, Value> newInterval {left, right};
    for (auto it = data_.begin(); it != data_.end(); ++it) {
        if (newInterval.second < it->first) {
            data_.insert(it, newInterval);
            return;
        } else if (newInterval.first <= it->first && newInterval.second >= it->first ||
                   newInterval.first > it->first && newInterval.first <= it->second) {
            newInterval = { std::min(newInterval.first, it->first), std::max(newInterval.second, it->second) };
            auto itTemp = it;
            itTemp--;
            data_.erase(it);
            it = itTemp;
        }
    }

    data_.insert(data_.end(), newInterval);
}

template<typename Key, typename Value>
fadeev::IntervalMap<Key, Value>::Intervals& fadeev::IntervalMap<Key, Value>::operator[](const Key& key) {
    std::function<Intervals&(std::unique_ptr<IMNode>&)> findLeafThenPlace = [&](std::unique_ptr<IMNode>& node) -> Intervals& {
        if (not node) {
            node = std::make_unique<IMNode>(key);
            size_++;
            return node->intervals;
        }

        if (node->key == key) {
            return node->intervals;
        }

        return key < node->key ? findLeafThenPlace(node->left) :
               findLeafThenPlace(node->right);
    };

    return findLeafThenPlace(root_);

}