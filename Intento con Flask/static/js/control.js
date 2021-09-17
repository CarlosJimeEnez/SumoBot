$("#go").on('input',function(){
$.ajax({
        url: '/GO',
        type: 'POST',
        data: {
        Button: $('#go').val()
        },
    
    success: function(response){
        console.log(response);
        },
        error: function(error){
        console.log(error);
        }
    })
})

$("#Righ_andleft").on("input",function(){

    $.ajax({
        url: '/Righ_andLeft',
        type: 'POST',
        data: {
        Righ_andLeft: $('#Righ_andleft').val()
        },
    
    success: function(response){
        console.log(response);
        },
        error: function(error){
        console.log(error);
        }
    })
})

$("#Media_vuelta").on("input",function(){
    $.ajax({
        url: '/Media_vuelta',
        type: 'POST',
        data: {
        media_vuelta: $('#Media_vuelta').val()
        },
    
    success: function(response){
        console.log(response);
        },
        error: function(error){
        console.log(error);
        }
    })
})

