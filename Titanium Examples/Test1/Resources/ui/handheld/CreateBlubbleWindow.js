function CreateBlubbleWindow(title) {	
	PhotoBlubbleWindow = require('ui/handheld/PhotoBlubbleWindow');
	
	var self = Ti.UI.createWindow({
		title:title,
		backgroundColor:'#5e9268',
		borderWidth:8,
		borderColor:'#999',
		top:150,
		height:200,
		width:300,
		borderRadius:10,
		opacity:1,
		transform:t,
		layout:'vertical'
	});
		
	var t = Titanium.UI.create2DMatrix();
	t = t.scale(0);	

	var body = Ti.UI.createView({height:Ti.UI.SIZE, 
		layout:'vertical', 
		center:0});
	
	var bodyView1 = Ti.UI.createView({center:0,
	top:40,
	layout:'vertical'});
	body.add(bodyView1);
	
	self.add(body);
		
	var blubbleNameTextBox = Ti.UI.createTextField({hintText:'Blubble Name',
	center:0,
	top:10,
	borderColor:'black',
	backgroundColor:'white',
	height:25,
	width:'80%',
	textAlign:'center',
	font:{fontFamily:'Calibri',fontSize:14,fontWeight:'regular'}});
	bodyView1.add(blubbleNameTextBox);
	
	var createBlubbleButton = Ti.UI.createButton({title:'Create',
	center:0,
	top:10,
	height:25,
	width:200,
	backgroundColor:'#0b5401',
	color:'white',
	borderRadius:3,
	font:{fontFamily:'Copperplate',fontSize:14,fontWeight:'regular'}});
	bodyView1.add(createBlubbleButton);

	createBlubbleButton.addEventListener('click', function(e){
		var t3 = Titanium.UI.create2DMatrix();
		t3 = t3.scale(0);
		self.close({transform:t3,duration:300});
		
		Ti.App.Properties.setString('CurrentPhotoBubble',blubbleNameTextBox.value);
		var photoBlubbleWindow = new PhotoBlubbleWindow({title:"PhotoBlubble",
		modal:true});

		// create first transform to go beyond normal size
		var t1 = Titanium.UI.create2DMatrix();
		t1 = t1.scale(1.1);
		var a = Titanium.UI.createAnimation();
		a.transform = t1;
		a.duration = 200;
	
		// when this animation completes, scale to normal size
		a.addEventListener('complete', function()
		{
			Titanium.API.info('here in complete');
			var t2 = Titanium.UI.create2DMatrix();
			t2 = t2.scale(1.0);
			photoBlubbleWindow.animate({transform:t2, duration:200});
		});

		photoBlubbleWindow.open(a);
		});

	var closeBlubbleButton = Ti.UI.createButton({title:'Close',
	center:0,
	top:10,
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

	return self;
};

module.exports = CreateBlubbleWindow;