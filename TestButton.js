import React from 'react'

let _url = 'http://localhost:8080/player';

function doSth(){
    console.log("--dziala--");
    fetch(_url)
        .then(res => {return res.json()})
        .then(data=> {console.log(data)});

}

/*
  useEffect(()=>{
    getData()
  },[])
*/

function TestButton(props){
    return (
        <input 
            type = 'button'
            value = {props.caption}
            className = "my_button"
            onClick = {doSth.bind()}
        />
    );
}

export default TestButton;