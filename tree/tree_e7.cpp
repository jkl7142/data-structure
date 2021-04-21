/*
*   Exercise 7 : Ʈ�� ���� �����
*/

#include <iostream>
#include <queue>

// ���� Ʈ�� ���
struct node {
    std::string position;
    node* first;
    node* second;
};

// ��Ʈ ���
struct org_tree {
    node* root;

    // ��Ʈ ��� ����
    static org_tree create_org_structure(const std::string& pos) {
        org_tree tree;
        tree.root = new node {pos, NULL, NULL};
        return tree;
    }

    // Ư�� ��å �̸��� �ش��ϴ� ��带 ã�Ƽ� ��ȯ
    static node* find(node* root, const std::string& value) {
        if (root == NULL)
            return NULL;
        
        if (root->position == value)
            return root;

        // first ��带 ���� Ž��
        auto firstFound = org_tree::find(root->first, value);

        if (firstFound != NULL)
            return firstFound;

        // second ��� Ž��
        return org_tree::find(root->second, value);
    }

    // ��� ����
    bool addSubordinate(const std::string& manager, const std::string& subordinate) {
        auto managerNode = org_tree::find(root, manager);

        if (!managerNode) {
            std::cout << manager << "��(��) ã�� �� �����ϴ�: " << std::endl;
            return false;
        }

        if (managerNode->first && managerNode->second) {
            std::cout << manager << " �Ʒ��� " << subordinate << "��(��) �߰��� �� �����ϴ�." << std::endl;
            return false;
        }

        if (!managerNode->first)
            managerNode->first = new node {subordinate, NULL, NULL};
        else
            managerNode->second = new node {subordinate, NULL, NULL};

        std::cout << manager << " �Ʒ��� " << subordinate << "��(��) �߰��߽��ϴ�." << std::endl;

        return true;
    }
};

int main() {

    auto tree = org_tree::create_org_structure("CEO");

    tree.addSubordinate("CEO", "�λ���");
    tree.addSubordinate("�λ���", "IT����");
    tree.addSubordinate("�λ���", "�����ú���");
    tree.addSubordinate("IT����", "��������");
    tree.addSubordinate("IT����", "�۰�������");
    tree.addSubordinate("�����ú���", "��������");
    tree.addSubordinate("�����ú���", "ȫ������");
    tree.addSubordinate("�λ���", "�繫����");

    return 0;
}