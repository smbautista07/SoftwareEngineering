var a_num = 1243; //float numbers only

var a_string = "this is a string";

var a_class = {param1: 43232322, param2: "str"}; 

var an_array = ["value1", "value2"];

let local_variable = 42;

var condition = true;

if (condition)
{
    //code_block
}

var condition2 = true;

if (condition && condition2)
{
    //console.log("condition1 AND condition2 are true");
}

var condition_based_variable=(condition)?"value_if_true":"value_if_false";

var what = a_num+a_string; //numbers auto convert to string for concatenation.

//console.log(what);

2<12; //true
2< "12"; //true
2< "John" // false
2>"John" //false

3 == "3"// true (is equal)
3 === "3" // false (not identiacal to)

var i = 0;
while(i<10)
{
    text = "The number is"+i;
    console.log(text);
    i++
}



var comp1 = "5";

console.log(2 < "12");