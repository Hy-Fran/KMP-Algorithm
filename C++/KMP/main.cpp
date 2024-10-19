#include <iostream>
#include <cstring>
#include <exception>

using std::string;

int* BuildMoveState(string pattern) {
    if (pattern.length() == 0)
    {
        throw std::invalid_argument("�ַ������Ȳ���Ϊ0");
    }
    int pattern_length = pattern.length();
    int move_state_length = pattern_length + 1;
    //moveState״̬�������pattern�����Ƕ�һ���ģ����һ��״̬��ʾ��ֹ״̬
    int* move_state = new int[move_state_length];
    int revert_state = 0;
    /*
    ״̬��0��1�϶���û�й���ǰ��׺, ���Ի��ݿ϶��ǻص�״̬0
     */
    move_state[0] = 0;
    move_state[1] = 0;

    int state = 2;
    while (state < move_state_length) {
        int suffixIndex = state - 1;
        //pattern.charAt(revertState)Ϊ������һ��״̬��Ҫ���ַ�
        if (pattern.at(suffixIndex) == pattern.at(revert_state)) {
            revert_state++;
            move_state[state] = revert_state;
            state++;
        }
        else {
            if (revert_state > 0) {
                revert_state = move_state[revert_state];
                //���ﲻ������һ�׶�����Ϊ������ ��ʱҪ�Ա�suffixIndex�������һ��״̬������ַ��Ƿ�һ��
            }
            else {
                //��ʱ�Ѿ���0״̬ �ƽ�state����
                state++;
            }
        }
    }
    return move_state;
}

int Search(string text, string pattern) {
    int* move_state = BuildMoveState(pattern);
    int move_state_length = pattern.length() + 1;
    /* ������i ��Ϊÿ��text��Ϊһ�����е����ĵ�һ��Ԫ�ص�popΪ�����״̬���ж��Ƿ������һ��״̬ */
    int input = 0;
    int state = 0;
    while (input < text.length()) {
        //pattern.charAt(state)Ϊ������һ��״̬��Ҫ���ַ�
        if (text.at(input) == pattern.at(state)) {
            state++;
            input++;
            if (state == move_state_length - 1) {
                delete [] move_state;
                return input - pattern.length();
            }
        }
        else {
            if (state > 0) {
                state = move_state[state];
                //���ﲻ����input++, ��Ϊ���ݺ�Ҫ�鿴������ڻ��ݺ������һ��״̬������
            }
            else {
                //��״ֱ̬���ƽ�
                input++;
            }
        }
    }
    delete [] move_state;
    return -1;
}

int main()
{
    string text = "ABBBBCBCBBBD";
    string pattern = "BBBD";
    int actual = Search(text, pattern);
    int expect = text.find(pattern);
    std::cout << "Expect: " << expect << std::endl;
    std::cout << "Acutal: " << actual << std::endl;
    return 0;
}
