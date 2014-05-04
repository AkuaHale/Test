function PhotoBlubbleWindow(title) {	
	
	Ti.include('./ui/common/chat/pubnub-chat.js');
		
	var self = Ti.UI.createWindow({
		title:title,
		backgroundColor:'#5e9268',
		layout:'vertical'
	});
		
	var t = Titanium.UI.create2DMatrix();
	t = t.scale(0);	

	var body = Ti.UI.createView({height:Ti.UI.SIZE, 
		layout:'vertical', 
		center:0});
	
	var bodyView1 = Ti.UI.createView({center:0,
	top:10,
	layout:'vertical'});
	body.add(bodyView1);
	
	self.add(body);
		
	var headerLabel = Ti.UI.createLabel({text:'Photo Blubble',
	center:0,
	font:{fontFamily:'Papyrus',fontSize:30,fontWeight:'bold'},
	color:'#0b5401'});
	bodyView1.add(headerLabel);
	
	var photoBubbleUser = Ti.App.Properties.getString('PhotoBubbleUserName');
	var greetingLabel = Ti.UI.createLabel({text:'Welcome '+photoBubbleUser,
	center:0,
	font:{fontFamily:'Copperplate',fontSize:18,fontWeight:'regular'},
	color:'#0b5401'});
	bodyView1.add(greetingLabel);
	
	var blubbleName = Ti.App.Properties.getString('CurrentPhotoBubble');
	var blubbleLabel = Ti.UI.createLabel({text:blubbleName + ' is up...',
	center:0,
	font:{fontFamily:'Copperplate',fontSize:18,fontWeight:'regular'},
	color:'#0b5401'});
	bodyView1.add(blubbleLabel);
	
	var closeBlubbleButton = Ti.UI.createButton({title:'Close',
	center:0,
	top:0,
	height:25,
	width:200,
	backgroundColor:'#0b5401',
	color:'white',
	borderRadius:3,
	font:{fontFamily:'Copperplate',fontSize:14,fontWeight:'regular'}});
	bodyView1.add(closeBlubbleButton);

	closeBlubbleButton.addEventListener('click', function(e){
		var t3 = Titanium.UI.create2DMatrix();
		t3 = t3.scale(0);
		self.close({transform:t3,duration:300});
		});

	var pubnub_chat_window = Ti.App.Chat({
	    "chat-room" : "my-random-conversation",
	    "window"    : {
	        title           : 'My Chat Room',
	        backgroundColor : '#fff'
	    },
	    "view"    : {
	        backgroundColor : '#fff'
	    }
	});
	bodyView1.add(pubnub_chat_window.chat_view);
	
	return self;
};

module.exports = PhotoBlubbleWindow;