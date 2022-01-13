// Created by Dan10022002 on 08.01.2022

#include <atomic>
template<typename T>
struct Node
{
    T data;
    Node* next;
    Node(const T& data) : data(data), next(nullptr) {}
};
 
template<typename T>
class LockFreeStack
{
    std::atomic<Node<T>*> head;
 public:
 
    // std::memory_order_relaxed не накладывает никаких ограничений,
        // необходима для гарантирования атомарности операции
      
        // std::memory_order_release необходима для того, чтобы
        // запись и чтение в текущем потоке не могли быть переупорядочены,
        // и другие потоки могли видеть данную атомарную переменную
      
        // compare_exchange_weak побитово сравнивает lhs и rhs и меняет
        // lhs на des только когда lhs и rhs побитово равны
    
    void Push(const T& data) {
        Node<T>* new_node = new node<T>(data);
        new_node->next = head.load(std::memory_order_relaxed); 
        while (!head.compare_exchange_weak (new_node->next, new_node,
                                        std::memory_order_release,
                                        std::memory_order_relaxed));
    }
    
    bool TryPop(T& value) {
        Node<T>* old_head = head.load(std::memory_order_relaxed);
        while (old_head && !head.compare_exchange_weak (old_head, old_head -> next,
                                                        std::memory_order_relaese,
                                                        std::memory_order_relaxed));
        if (!old_head){
            return false;
        } else {
            value = old_head -> data;
            delete old_head;
            return true;
        }
    }

};

// Дальше идёт реализация из лекции Бородина

  template <typename T>
  struct LockFreeStack {
    void Push(const T& value);
    Node* Pop();

    struct Node {
      T data;
      Node* next;
   };
  private:
   std::atomic<Node*> head_;
 };
  void Push(const T& value) {
      Node* new_head = new Node(value, head_.load());

      while (

        !head_.compare_exchange_weak(new_head->next, new_head)

      ) { }
  }
  bool Node* Pop() {
    Node* node = head_.load();

    while (node &&

      !head_.compare_exchange_weak(node, node->next)

    ) { }

   return node ? true : false;
 }
