"use strict";

function getRandomInt(max)
{
    return Math.floor(Math.random()*max)
}



class inputHandler
{
    static #inputs = new Set();

    static getInputs()
    {
        return this.#inputs;
    }
    
    static checkKey(key)
    {
        return this.#inputs.has(key);
    }

    static addToSet(value)
    {
        this.#inputs.add(value);
    }
    static removeFromSet(value)
    {
        this.#inputs.delete(value);
    }

    static updateInputs(event)
    {
        (event.type == "keydown") ? inputHandler.addToSet(event.code):inputHandler.removeFromSet(event.code);
    }
}

document.addEventListener("keydown", inputHandler.updateInputs);
document.addEventListener("keyup", inputHandler.updateInputs);

class rectObj
{
    constructor(x, y, width = 0, height = 0)
    {
        this.x = x;
        this.y = y;
        this.width = width;
        this.height = height;
        this.xSpeed;
        this.ySpeed;
    }
}

class rectCollider extends rectObj
{
    constructor(x, y, width, height)
    {
        super(x,y,width, height);
    }
    


    isCollidingWith(otherObj)
    {
        let xLeft = this.x;
        let xRight = this.x+this.width; //may need to use trig for rotated shapes.
        let yTop = this.y; //same for this
        let yBottom = this.y + this.height;
        let theirXLeft = otherObj.x;
        let theirXRight = otherObj.x+otherObj.width;
        let theirYTop = otherObj.y;
        let theirYBottom = otherObj.y+otherObj.height; 
            // if (xRight< theirXLeft)
            // {
            //     console.log("ball is to the left");
            // }
            // if (xLeft > theirXRight)
            // {
            //     console.log("ball is to the right");
            // }
            if (xRight >= theirXLeft && xLeft <= theirXRight)
            {
                // console.log("ball is x aligned");
                if (yTop <= theirYBottom && yBottom >= theirYTop) // y axis aligned
                {
                    return true;
                }
            }            
        // if (xLeft < theirXRight || xRight > theirXLeft) //x axis aligned
        // {
        //         console.log("x axis aligned");
        //     if (yTop < theirYBottom || yBottom > theirYTop) // y axis aligned
        //     {
        //         console.log("COLLIDING");
        //     }
        // }
    }
}



class pongBall extends rectCollider
{
    constructor()
    {
        super(470,260,20,20)
        this.xSpeed = 5;
        this.ySpeed = 5;
        this.xPrev;
        this.yPrev;
    }
    
    update()
    {
        this.xPrev = this.x;
        this.yPrev = this.y;   
        this.x += this.xSpeed;
        this.y += this.ySpeed;
        if (this.x > 960-this.width || this.x < 0)
        {
            this.xSpeed *= -1;
        }
        if (this.y >540-this.height || this.y < 0)
        {
            this.ySpeed *= -1;
        }
    }
    move(xPosition, yPosition)
    {
        
    }
    setPosition(newX, newY)
    {

    }
}

class paddle extends rectObj
{
    constructor(x, y, width = 0, height = 0, up_in, down_in)
    {
        super(x, y, width, height);
        this.up = up_in;
        this.down = down_in;
    }

    move(y_in)
    {
        this.y += y_in;
    }

    update()
    {
        this.yPrev = this.y
        // console.log(inputHandler.getInputs())
        if (inputHandler.checkKey(this.up))
        {
            this.ySpeed = -5;
        }
        else if (inputHandler.checkKey(this.down))
        {
            this.ySpeed = 5;
        }
        else
        {
            this.ySpeed = 0;
        }

        this.y += this.ySpeed;
    }
}

document.addEventListener('DOMContentLoaded', start);

const para = document.createElement('p');
const words = document.createTextNode("Hi");

para.appendChild(words);
const paragraph = document.getElementById("oops");
// document.body.insertBefore(para,paragraph);

document.body.appendChild(para);

var canvas = document.createElement("canvas"); 
canvas.width = 960;
canvas.height = 540;
canvas.id = "screen";

document.body.insertBefore(canvas,paragraph);

var ctx = canvas.getContext("2d");

function start()
{
    
}
/*
function drawBackground()
{
    ctx.fillStyle="black";
    ctx.fillRect(0,0,canvas.width,canvas.height);
}
*/


const ball = new pongBall();

const leftPaddle = new paddle(50, 270, 10, 100, "KeyW", "KeyS");
const rightPaddle = new paddle(960-50-10, 270, 10, 100, "ArrowUp", "ArrowDown");

const wall = new rectObj(0,0,10,540);
const wall2 = new rectObj(950,0,10,540);


var player1Score = 0;
var player2Score = 0;

render();
ctx.fillStyle = "black";
ctx.fillRect(wall.x,wall.y,wall.width,wall.height)
ctx.fillRect(wall2.x,wall2.y,wall2.width,wall2.height)


function clearScore()
{
    ctx.clearRect(430,30,100,80)
}
function drawScore()
{

    let scoreText =  `${player1Score}:${player2Score}`;
    ctx.font = "50px serif";
    ctx.textAlign = "center";
    ctx.fillText(scoreText,480,70);
}

function render()   
{
    ctx.fillStyle = "black";

    drawScore();
    ctx.clearRect(ball.xPrev,ball.yPrev,ball.width,ball.height);
    ctx.fillRect(ball.x,ball.y,ball.width,ball.height);
    
    ctx.clearRect(leftPaddle.x,leftPaddle.yPrev,leftPaddle.width,leftPaddle.height);
    ctx.fillRect(leftPaddle.x,leftPaddle.y,leftPaddle.width,leftPaddle.height);

    ctx.clearRect(rightPaddle.x,rightPaddle.yPrev,rightPaddle.width,rightPaddle.height);
    ctx.fillRect(rightPaddle.x,rightPaddle.y,rightPaddle.width,rightPaddle.height);

}

ctx.fillRect(rightPaddle.x,rightPaddle.y,rightPaddle.width,rightPaddle.height);
ctx.fillRect(rightPaddle.x,rightPaddle.y,rightPaddle.width,rightPaddle.height);

var contactFlag = false;

var wallFlag = false;

function drawRectObj(rectangle)
{
    ctx.fillRect(rectangle.x,rectangle.y,rectangle.width,rectangle.height);
}

function clearRectObj(rectangle)
{
    ctx.clearRect(rectangle.xPrev,rectangle.yPrev,rectangle.width,rectangle.height);
}

function update()
{
    //currentInputs = inputHandler.

    ball.update();
    // if (ball.isCollidingWith(wall))
    // {
    //     ball.xSpeed*=-1;
    //     ball.ySpeed*=-1;
    // }

    if (ball.isCollidingWith(leftPaddle))
    {
        if (!contactFlag)
        {
            ball.xSpeed += 1;
            ball.xSpeed = (Math.abs(ball.xSpeed) + 1) * (ball.xSpeed/Math.abs(ball.xSpeed))*-1
            ball.ySpeed += Math.round(leftPaddle.ySpeed/2);
        }
        contactFlag = true;
    }
    else if (ball.isCollidingWith(rightPaddle))
    {
        if (!contactFlag)
        {
            ball.xSpeed = (Math.abs(ball.xSpeed) + 1) * (ball.xSpeed/Math.abs(ball.xSpeed))*-1
            ball.ySpeed += Math.round(rightPaddle.ySpeed/2);
        }
        contactFlag = true;
    }
    else 
    {
        contactFlag = false;
    }


    leftPaddle.update();
    rightPaddle.update();
   

    if (ball.isCollidingWith(wall))
    {
        if (wallFlag == false)
        {
            player2Score += 1;
            clearScore();    
            drawScore();
            drawRectObj(wall);
            wallFlag = true;
        }
    }
    else if (ball.isCollidingWith(wall2))
    {
        if (wallFlag == false)
        {
            player1Score += 1;
            clearScore();
            drawScore();
            drawRectObj(wall2);
            wallFlag = true;
        }
    }


    if (wallFlag == true)
    {
        ball.x = 470;
        ball.y = 260;
        ball.xSpeed = getRandomInt(10)-5;
        ball.ySpeed = getRandomInt(10)-5;
        if (Math.abs(ball.xSpeed) < 2)
        {
            ball.xSpeed = 2 * (Math.abs(ball.xSpeed)/ball.xSpeed);
        }
        wallFlag = false;
    }
    
    console.log(ball.x, ball.y);

    // console.log(ball);
    render();
}



setInterval(update,10);

//document.addEventListener("DOMContentLoaded", loadTools());