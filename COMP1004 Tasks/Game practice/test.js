var canvas = document.createElement("canvas", {width : "960", height : "540"});
var ctx = canvas.getContext("2d");

document.body.appendChild(canvas);

ctx.fillRect(50,50,50,50);

setInterval(update,10);
//setInterval(updateAlt, 20);


class inputHandler
{
    
    // constructor()
    // {
        
    //     // this.key_map = new Map(['e', false]);
    // }
    // addKey(character)
    // {
    //     this.key_map.set(character,true);
    // }
    // removeKey(character)
    // {
    //     this.key_map.set(character, false);
    // }
    // getKey(character)
    // {
    //     return this.key_map.get(character);
    // }

    // TESTING STATIC METHOD VIABILITY
    static #property = new Map();
    static testMethod()
    {
        return this.#property;
    }
    static addToProperty(key, value)
    {
        this.#property.set(key, value);
    }
    
    static #experimentalSet = new Set();
    static returnSet()
    {
        return this.#experimentalSet;
    }
    static addToSet(value)
    {
        this.#experimentalSet.add(value);
    }
    static removeFromSet(value)
    {
        this.#experimentalSet.delete(value);
    }
}

function updateAlt()
{
    console.log("Hi");
}
// var key_map = new Map() 

//var inputhandler =  inputHandler();

class testClass1
{
    constructor()
    {
        this.attr1 = "testClass1";
    }

    methodT()
    {
        console.log(this.attr1);
    }

    methodU()
    {
        console.log(this.attr1);
    }
}

class testClass2 extends testClass1
{
    constructor()
    {
        super();
        this.attr2 = "testClass2";
    }

    methodT()
    {
        super.methodT();
        console.log(this.attr2);
    }
}
document.addEventListener("keydown", input_add);
document.addEventListener("keyup", input_add);

var testObj1 = new testClass1(); 

var testObj2 = new testClass2();


function update()
{
    
    // ctx.fillRect(size,size,size,size);
    // size+=1;

    // document.addEventListener("keydown", input_add);
    // document.addEventListener("keyup", input_remove);


    // if (key_map.get('e') == true)
    // {
    //     console.log("e is true");
    // }
    // if (key_map.get('d') == true)
    // {
    //     console.log("d is true");
    // }


    //console.log(inputHandler.getKey('e'));
    //console.log(inputhandler.key_map);
    //console.log(inputHandler.property);

    //console.log(inputHandler.testMethod());
    //inputHandler.addToProperty('e',true);

    
    // testObj1.methodT();
    testObj2.methodT();
    // console.log(inputHandler.returnSet());


    //document.addEventListener("keydown", keyEvent);
}

//Writeup purposes only
// function keyEvent(eventInfo)
// {
//     console.log(eventInfo.code);
// }

function input_add(event)
{

    // console.log(e.key);
    // inputHandler.addKey(e.key);
    // key_map.set(e.key, true);
    //console.log(e.key);
    
    //inputHandler.addToProperty(e.key, e.type == 'keydown');

    if (event.type == "keydown")
    {
        inputHandler.addToSet(event.key );
    }
    else
    {
        inputHandler.removeFromSet(event.key);
    }

    //FINAL
    // (event.type == "keydown") ? inputHandler.addToSet(event.code):inputHandler.removeFromSet(event.code);

    //console.log(e);
}

function input_remove(e)
{
    console.log(e);
    // inputHandler.removeKey(e.key);
    //key_map.set(e.key, false);
}

