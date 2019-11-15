/*
 * @lc app=leetcode id=855 lang=cpp
 *
 * [855] Exam Room
 *
 * https://leetcode.com/problems/exam-room/description/
 *
 * algorithms
 * Medium (40.15%)
 * Total Accepted:    20.9K
 * Total Submissions: 51.7K
 * Testcase Example:  '["ExamRoom","seat","seat","seat","seat","leave","seat"]\n[[10],[],[],[],[],[4],[]]'
 *
 * In an exam room, there are N seats in a single row, numbered 0, 1, 2, ..., N-1.
 * 
 * When a student enters the room, they must sit in the seat that maximizes the
 * distance to the closest person.  If there are multiple such seats, they sit
 * in the seat with the lowest number.  (Also, if no one is in the room, then
 * the student sits at seat number 0.)
 * 
 * Return a class ExamRoom(int N) that exposes two functions: ExamRoom.seat()
 * returning an int representing what seat the student sat in, and
 * ExamRoom.leave(int p) representing that the student in seat number p now
 * leaves the room.  It is guaranteed that any calls to ExamRoom.leave(p) have
 * a student sitting in seat p.
 * 
 * Example 1:
 * Input: ["ExamRoom","seat","seat","seat","seat","leave","seat"],
 * [[10],[],[],[],[],[4],[]]
 * Output: [null,0,9,4,2,null,5]
 * Explanation:
 * ExamRoom(10) -> null
 * seat() -> 0, no one is in the room, then the student sits at seat number 0.
 * seat() -> 9, the student sits at the last seat number 9.
 * seat() -> 4, the student sits at the last seat number 4.
 * seat() -> 2, the student sits at the last seat number 2.
 * leave(4) -> null
 * seat() -> 5, the student sits at the last seat number 5.
 *
 * Note: 
 * 1 <= N <= 10^9
 * ExamRoom.seat() and ExamRoom.leave() will be called at most 10^4 times across all test cases.
 * Calls to ExamRoom.leave(p) are guaranteed to have a student currently sitting in seat number p.
 *
 * 房间里有一排N个座位，编号为0, 1, 2, ..., N-1。
 * 学生进入房间时选择距离最近的人最远的位置就坐。当存在多个满足条件的座位时，选择标号最小的。
 * 学生也可以离开座位。
 * 求每一位学生就坐时的位置。
 * 
 * @Category TreeSet
 * @Idea TreeSet T=O(n) S=O(n)
 * start=连续空位的起点,初始化为0(左墙),i为当前访问到的有人的座位位置,mx=当前找到的离人最远距离
 * 扫描所有有人的位置:
 *   若连续空位连着左墙,看选左墙位置(0)是否最佳
 *   否则连续空位在两人之间,看选正中间是否最佳
 * 最后看是否能坐右墙且最佳
 */
class ExamRoom {
public:
    ExamRoom(int N) {
        n = N;
    }
    
    // start=连续空位的起点,初始化为0(左墙),i为当前访问到的有人的座位位置,mx=当前找到的离人最远距离
    // 扫描所有有人的位置:
    //   若连续空位连着左墙,看选左墙位置(0)是否最佳
    //   否则连续空位在两人之间,看选正中间是否最佳
    // 最后看是否能坐右墙且最佳
    // T=O(n) S=O(n)
    int seat() {
        int start = 0, mx = 0, idx = 0;         // start=连续空位的起点,mx=离人最远的距离,idx=当前找的最合适空位
        for (int i : occupied) {                // 扫描每个被占的座位号    
            if (start == 0) {                   //   若连续空位靠左墙
                if (mx < i - start) {           //     看选左墙位置是否会有更远的离人距离,若有则更新mx和idx
                    mx = i - start;
                    idx = 0;
                }
            } else {                            //   若连续空位不靠左墙(在两个人之间)
                if (mx < (i - start + 1) / 2) { //     看选两人中间位置是否会有更远的离人距离,若有则更新mx和idx
                    mx = (i - start + 1) / 2;
                    idx = start + mx - 1;
                }
            }
            start = i + 1;                      //   更新连续空位起点=当前被占座位的下一个位置
        }
        if (start > 0 && mx < n - start) {      // 最后看是否可坐靠右墙位置且是否会有更远的离人距离,若有则更新mx和idx
            mx = n - start;
            idx = n - 1;
        }
        occupied.insert(idx);                   // 坑: 别忘占坐!!
        return idx;                             // 返回选的最佳位置
    }
    
    void leave(int p) {
        occupied.erase(p);
    }
private:
    int n;                                      // 总共座位数
    set<int> occupied;                          // 已被占的座位号
};

/**
 * Your ExamRoom object will be instantiated and called as such:
 * ExamRoom* obj = new ExamRoom(N);
 * int param_1 = obj->seat();
 * obj->leave(p);
 */
