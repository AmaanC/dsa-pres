(function() {
    var infixElem = document.getElementById('infix');
    var postfixElem = document.getElementById('postfix');
    var infixExp = '';
    var stack = [];

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
                    console.log('Pushing', c);
                }
                else {
                    while (stack.length > 0) {
                        temp = stack.pop();
                        postExp += temp;
                    }
                    stack.push(c);
                }
            }
        }
        while (stack.length > 0) {
            temp = stack.pop();
            postExp += temp;
        }
        return postExp;
    };

    infixElem.addEventListener('input', function() {
        infixExp = this.value;
        postfixElem.textContent = convert(infixExp);
    }, false);
})();