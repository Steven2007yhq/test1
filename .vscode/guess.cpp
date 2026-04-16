// 全局变量
let socket;
let currentUser = 'user_' + Math.floor(Math.random() * 1000000);

// 页面加载完成后执行
document.addEventListener('DOMContentLoaded', function() {
    // 初始化WebSocket连接
    initSocket();
    
    // 添加回车键发送消息功能
    document.getElementById('message-input').addEventListener('keydown', function(e) {
        if (e.key === 'Enter' && !e.shiftKey) {
            e.preventDefault();
            sendMessage();
        }
    });
});

// 初始化WebSocket连接
function initSocket() {
    socket = io();
    
    // 连接成功事件
    socket.on('connect', function() {
        console.log('WebSocket连接成功');
    });
    
    // 接收AI回复字符
    socket.on('response', function(data) {
        if (data.user_id === currentUser) {
            displayAssistantChar(data.char);
        }
    });
    
    // 接收AI回复结束事件
    socket.on('response_end', function(data) {
        if (data.user_id === currentUser) {
            endAssistantMessage();
        }
    });
    
    // 连接断开事件
    socket.on('disconnect', function() {
        console.log('WebSocket连接断开');
    });
}

// Markdown转义函数，处理**相关试剂**这样的Markdown语法
function escapeMarkdown(text) {
    // 替换Markdown语法，防止显示原始Markdown标签
    return text
        // 移除加粗语法 **内容**
        .replace(/\*\*(.*?)\*\*/g, '$1')
        // 移除斜体语法 *内容* 或 _内容_
        .replace(/\*(.*?)\*/g, '$1')
        .replace(/_(.*?)_/g, '$1')
        // 移除标题语法 # 内容
        .replace(/^#\s*(.*?)$/gm, '$1')
        // 移除列表语法 - 或 *
        .replace(/^(\s*)[-*]\s*(.*?)$/gm, '$2')
        // 移除链接语法 [文本](链接)
        .replace(/\[(.*?)\]\((.*?)\)/g, '$1')
        // 移除代码块 ```内容```
        .replace(/```([\s\S]*?)```/g, '$1')
        // 移除行内代码 `内容`
        .replace(/`(.*?)`/g, '$1');
}

// 显示AI回复字符
function displayAssistantChar(char) {
    let chatMessages = document.getElementById('chat-messages');
    let lastMessage = chatMessages.lastElementChild;
    
    // 转义Markdown字符
    let escapedChar = escapeMarkdown(char);
    
    if (!lastMessage || !lastMessage.classList.contains('message') || !lastMessage.classList.contains('assistant')) {
        // 创建新的AI消息元素
        let assistantMessage = document.createElement('div');
        assistantMessage.className = 'message assistant';
        assistantMessage.id = 'current-assistant-message';
        assistantMessage.textContent = escapedChar;
        chatMessages.appendChild(assistantMessage);
    } else {
        // 追加到现有AI消息
        lastMessage.textContent += escapedChar;
    }
    
    // 滚动到底部
    chatMessages.scrollTop = chatMessages.scrollHeight;
}

// 结束AI回复
function endAssistantMessage() {
    let currentMessage = document.getElementById('current-assistant-message');
    if (currentMessage) {
        currentMessage.removeAttribute('id');
    }
}

// 发送消息
function sendMessage() {
    let input = document.getElementById('message-input');
    let message = input.value.trim();
    
    if (message) {
        // 显示用户消息
        displayUserMessage(message);
        
        // 清空输入框
        input.value = '';
        
        // 发送消息到服务器
        socket.emit('message', {
            user_id: currentUser,
            message: message
        });
        
        // 创建AI回复的初始元素
        let chatMessages = document.getElementById('chat-messages');
        let assistantMessage = document.createElement('div');
        assistantMessage.className = 'message assistant';
        assistantMessage.id = 'current-assistant-message';
        chatMessages.appendChild(assistantMessage);
        chatMessages.scrollTop = chatMessages.scrollHeight;
    }
}

// 显示用户消息
function displayUserMessage(message) {
    let chatMessages = document.getElementById('chat-messages');
    let userMessage = document.createElement('div');
    userMessage.className = 'message user';
    userMessage.textContent = message;
    chatMessages.appendChild(userMessage);
    chatMessages.scrollTop = chatMessages.scrollHeight;
}

// 显示模块
function showModule(moduleName) {
    // 隐藏所有模块
    let modules = document.querySelectorAll('.module');
    modules.forEach(module => {
        module.classList.remove('active');
    });
    
    // 移除所有菜单项的激活状态
    let menuItems = document.querySelectorAll('.menu-item');
    menuItems.forEach(item => {
        item.classList.remove('active');
    });
    
    // 显示选中的模块
    let selectedModule = document.getElementById(moduleName + '-module');
    if (selectedModule) {
        selectedModule.classList.add('active');
    }
    
    // 激活对应的菜单项
    let selectedMenuItem = event.target;
    selectedMenuItem.classList.add('active');
}



// 生成演讲稿
function generateSpeech(event) {
    event.preventDefault();
    
    let topic = document.getElementById('speech-topic').value.trim();
    let keywords = document.getElementById('speech-keywords').value.trim();
    
    if (!topic) {
        alert('请输入演讲主题');
        return;
    }
    
    let speechResult = document.getElementById('speech-result');
    speechResult.textContent = '正在生成演讲稿...';
    
    fetch('/api/generate_speech', {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json',
        },
        body: JSON.stringify({
            topic: topic,
            keywords: keywords
        })
    })
    .then(response => response.json())
    .then(data => {
        speechResult.textContent = data.content;
    })
    .catch(error => {
        console.error('生成演讲稿出错:', error);
        speechResult.textContent = '生成演讲稿出错，请稍后重试';
    });
}