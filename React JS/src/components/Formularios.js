import React, {Fragment, useState} from 'react'

const Formularios = () => {

    const [datos, setDatos] = useState({
        nombre : ' ',
        apellido : ' '
    })

    const asignarNombre = (event) =>{
        setDatos({
            ...datos,
            [event.target.name] : event.target.value
        })

    }

    const mostrarDatos = (event) =>{
        event.preventDefault();
    }

    return ( 

        

        <Fragment>
            <div>Formulario</div>

            <form className = 'row' onSubmit = {mostrarDatos}>

                <div className = 'col-md-3'> 
                    <input placeholder = "Ingrese Nombre"
                           type = 'text'
                           onChange = {asignarNombre}
                           name = "nombre"
                           >
                            
                    </input>
                 </div>

                <div className = 'col-md-3'> 
                    <input placeholder = "Ingrese Apellido"
                           type = 'text'
                           onChange = {asignarNombre}
                           name = "apellido"
                           >

                    </input>
                 </div>

                <div className = 'col-md-3'> 
                    <button 
                        className = 'btn btn-primary' 
                        type='submit'>Enviar
                    </button>
                 </div>
                
            </form>
        </Fragment>
     );
}
 
export default Formularios;