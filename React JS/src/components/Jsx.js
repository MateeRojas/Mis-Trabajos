import React, { Fragment } from 'react'

const Jsx = () => {
    
    const temp = 21;
    
        return (  
            <Fragment>
            <h4>

            {
                temp > 50 ? 'frio' : 'calor'
            }

            </h4>
    </Fragment>
        );

}
 
export default Jsx;