import React, {Fragment, useState} from 'react'

const Lista = () => {

    const[array, setArray] = useState([1,2,3])
    const[num, setNum] = useState(4)

    const agregarElemento = () =>{
        setNum(num + 1)
        console.log('click')
        setArray([...array, num])
    }

    return( 
        <Fragment>
            <button onClick = {agregarElemento}>Agregar</button>
            <h2>
                {
                array.map((item, index )=>
                    <p key = {index}>
                        {item}
                    </p>
                
                )
            }
            </h2>
        </Fragment>
     );
}
 
export default Lista;