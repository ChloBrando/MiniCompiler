int a;
int b;
int c;
int sum;
int arr[5];
int i;
string s;
string t;
string u;
string hi;
hi = "hi there";
print(hi);

s = "hello";
t = "world";
u = s + " " + t;
print(u);

a = 5;
b = 7;
print("a = ");
print(a);
print("b = ");
print(b);

c = a + b + 3;
print("c = ");
print(c);

arr[0] = 1;
arr[1] = 2;
arr[2] = a + b;

i = 2;
arr[i] = arr[2] + c;

arr[4] = arr[0] + arr[1];
arr[3] = arr[0] + arr[1] + arr[4];

print("arr[0] = ");
print(arr[0]);
print("arr[1] = ");
print(arr[1]);
print("arr[2] = ");
print(arr[2]);
print("arr[3] = ");
print(arr[3]);
print("arr[4] = ");
print(arr[4]);

sum = arr[0] + arr[1] + arr[2] + arr[4];
print("sum = ");
print(sum);

print("arr[i] = ");
print(arr[i]);