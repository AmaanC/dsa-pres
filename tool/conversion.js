(function() {
    var form = document.getElementById('form');
    var infixElem = document.getElementById('infix');
    var infixExp = '';
    var stack = [];

    var canvas = document.getElementById('postfix');
    var ctx = canvas.getContext('2d');

    var distBet;
    var heightOffset;

    var DEFAULT_FONT = '20px Arial';
    var FONT_SIZE = parseInt(DEFAULT_FONT, 10);

    var DEFAULT_COLOR = 'black';
    var CHAR_COLOR = 'red';

    var START_HEIGHT = 30;
    var currentHeight;

    var isOperand = function(c) {
        return /[0-9a-zA-Z]/.test(c);
    };

    var seeTop = function(arr) {
        return arr[arr.length - 1];
    };

    var getPriority = function(op) {
        var val = 0;
        switch(op) {
            case '/':
                val = 4;
                break;
            case '*':
                val = 3;
                break;
            case '+':
                val = 2;
                break;
            case '-':
                val = 1;
                break;
            default:
                val = 0;
                break;
        }
        return val;
    };

    var higherPrecedence = function(op1, op2) {
        return getPriority(op1) > getPriority(op2);
    };

    var convert = function(inExp) {
        var postExp = '';
        var c = '';
        var temp;
        for (var i = 0; i < inExp.length; i++) {
            c = inExp[i];
            if (isOperand(c)) {
                postExp += c;
            }
            else {
                // It is an operator
                if (c === '(') {
                    stack.push(c);
                }
                else if (c === ')') {
                    temp = stack.pop();
                    while (temp != '(' && stack.length > 0) {
                        postExp += temp;
                        temp = stack.pop();
                    }
                }
                else if (stack.length === 0 || seeTop(stack) === '(' || higherPrecedence(c, seeTop(stack))) {
                    stack.push(c);
                }
                else {
                    while (stack.length > 0) {
                        temp = stack.pop();
                        postExp += temp;
                    }
                    stack.push(c);
                }
            }

            saveStep(c, postExp, stack);
        }
        while (stack.length > 0) {
            temp = stack.pop();
            postExp += temp;
        }
        saveStep('\\0', postExp, stack);
        return postExp;
    };

    var saveStep = function(c, postExp, stack) {
        ctx.fillStyle = CHAR_COLOR;
        ctx.fillText('Current character: \'' + c + '\'', 0, currentHeight);
        ctx.fillStyle = DEFAULT_COLOR;

        currentHeight += distBet;
        ctx.fillText('Stack: [\'' + stack.join('\', \'') + '\']', 0, currentHeight);
        currentHeight += distBet;
        ctx.fillText('Postfix expression: ' + postExp, 0, currentHeight);

        currentHeight += heightOffset;
    };

    var generate = function(e) {
        ctx.clearRect(0, 0, canvas.width, canvas.height);
        currentHeight = START_HEIGHT;
        distBet = FONT_SIZE;
        heightOffset = 2 * FONT_SIZE;

        infixExp = infixElem.value;
        canvas.height = infixExp.length * FONT_SIZE * 6;

        ctx.font = DEFAULT_FONT;

        convert(infixExp);
        if (e) {
            e.preventDefault();
        }
    };

    form.addEventListener('submit', generate, false);
    infixElem.focus();
    generate();
})();