
public class Test {

    public static void main(String[] args) {
        // System.out.println("Hello World! VSC");
        // int num = (int) (Math.random() * 100);
        // System.out.println("这是随机数 : " + num);

        char[] ss = { 'a', 'b', 'c', 'a', 'b', 'x' };
        int[] next = new int[225];
        get_next(ss, next);
    }

    /* 通过计算返回子串T的next数组。 */
    static void get_next(char[] T, int next[]) {
        int j = 0, k = -1;
        next[0] = -1;
        int len = T.length;
        while (j < len - 1) {
            if (k == -1 || T[j] == T[k]) {
                j++;
                k++;
                next[j] = k;
            } else
                k = next[k]; // 此语句是这段代码最反人类的地方，如果你一下子就能看懂，那么请允许我称呼你一声大神！
        }
    }
}
