# BANANA
A new data storing format. Similar to JSON, but tries to be much simpler

## Introduction

I came up with an idea to create a data storing format, that will be powerfull as well as JSON, but will need less amount of characters. 
So, I overfulfilled the plan, because the **BANANA** became even more powerfull.

## Question!

This is how it looks:
```
rect{
  w:150,
  h:50
}
integer:10
'float':51.5,
"boolean":true
string:string
```
This is how the same JSON file looks like:
```json
{
  "rect" : {
    "w" : 150,
    "h" : 50,
  },
  "integer" : 10,
  "float" : 51.5,
  "boolean" : true,
  "string" : "string"
}
```
The **BANANA**s variant looks a little better, huh?

So, how does it work? Let's discuss about the...

## Rules

### Syntax

1. As you can see, commas (`,`) aren't necessary. Every line break (basically, it is `\n` character) converts into comma (`,`) automatically;
2. Colon (`:`) is not necessary, if the value (of the key-value pair) is an array and the key is a string;
3. You don't need to use quotes to assign a string (for both keys and values) if it doesn't contain any of the characters: `,.:[]{}()\n\t\v` or it's equal to `none`, `true` or `false`;
4. Both single and double quotes are supported;
5. You can use any of the brackets: `()`, `[]`, `{}` to create an array. But the type of the opening bracket must match the type of the closing bracket;

### Storing

*In the chapter, examples will be written in C++*

Every **BANANA** object contains one of the data types:
* integer;
* float;
* string;
* boolean;
* endless array of **BANANA**s

So, you can create a multidimensioal array of arrays of strings, integers, floats, booleans and arrays (essentially: anything you want)

Something interesting: how to store key-value pair? I made it to be stored as an array of 2 elements: the key and the value. 
What does it mean? It means that an array of 3+ elements doesn't really differ from a key-value pair. Still not clear? Lets look at the example:
We'll take this **BANANA**:
```
10
12.5
[banana, orange, apple]
time:12am
```
And see how it looks in C++:
```cpp
bnn::banana bn = {
  10,
  12.5,
  { "banana", "orange", "apple" },
  { "time, "12am" }
}
```
Is this a good solution? No. Does this make data storing format powerful? Yes!

### Behaviour

Firstly, let's talk about the parser. There are several rules in his behavior (some of them will be copied from the Rules chapter):
1. Every line break (basically, it is `\n` character) converts into comma (`,`) automatically;
2. Colon (`:`) is not necessary, if the first value is a string and the second value is an array, they will be converted into the array of 2 elements automatically (as earlier explained);
3. If the parser meets a colon (`:`), it will create an array of 2 elements: the value before the colon (`:`) and the value after the colon (`:`);
4. You don't need to use quotes to assign a string (for both keys and values) if it doesn't contain any of the characters: `,.:[]{}()\n\t\v` or it's equal to `none`, `true` or `false`;

Secondly, let's talk about getting elelments from **BANANA**s (here will be described the solutions I made to work with data in C++):
1. if the **BANANA** object stores an integer, float, string or a boolean, then you can get that values by casting the object (conversion operators are present)
2. if the **BANANA** object stores an array, then there are 2 ways, how you can get data:
   - You can send an integer to the `operator[]` to get neede value by index in the object's array;
   - Or, you can send a string to the `operator[]` to launch the algorithm: 
   the method will walk through the object's array and check: if the current element of the array is an array of 2 elements `size() == 2` and the first of the elements is equals to the given parameter, then the method will return the second element of that 2 elements.
   If we didn't found the required value, the method will create an array of 2 elements: given parameter and undefined **BANANA** object.

## Summary
I've spend a week to create this, but the work isn't finished. I will be really happy if you suggest an idea or commit something to the project!
