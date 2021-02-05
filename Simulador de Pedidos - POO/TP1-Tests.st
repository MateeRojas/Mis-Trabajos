TestCase subclass: #AlgoPedidosTests
	| algoPedidos | 
	
	algoPedidos := AlgoPedidos new.
	algoPedidos crearPedidoConDeliveryPara: 'Sebas'.
	
	algoPedidos agregarProductoConNombre: 'Asado' precio: 500.0 yCantidad: 1 para: 'Sebas'.
	algoPedidos agregarMenuConNombre: 'Men√∫ Lunes' precio: 200.0 yCantidad: 1 para: 'Sebas'.
	algoPedidos agregarProductoConNombre: 'vino' precio: 250.0 yCantidad: 1 para: 'Sebas'.
	 
	self assert: (algoPedidos precioPedidoDe: 'Sebas') equals: (950*1.2). "20% extra"
	
	algoPedidos removerProductoConNombre: 'vino' para: 'Sebas'.
	algoPedidos removerMenuConNombre: 'Men√∫ Lunes' para: 'Sebas'.
	
	self assert: (algoPedidos precioPedidoDe: 'Sebas') equals: (500*1.2). "20% extra"! !
	| algoPedidos | 
	
	algoPedidos := AlgoPedidos new.
	algoPedidos crearPedidoConDeliveryPara: 'Santiago'.
	
	algoPedidos agregarProductoConNombre: 'Asado' precio: 500.0 yCantidad: 1 para: 'Santiago'.
	algoPedidos agregarProductoConNombre: 'vino' precio: 250.0 yCantidad: 1 para: 'Santiago'.
	 
	self assert: (algoPedidos precioPedidoDe: 'Santiago') equals: (750*1.2). "20% extra"! !
	| algoPedidos | 
	
	algoPedidos := AlgoPedidos new.
	algoPedidos crearPedidoParaRetirarPara: 'Carlos'.
	
	algoPedidos agregarMenuConNombre: 'Men√∫ viernes' precio: 200.0 yCantidad: 1 para: 'Carlos'.
	algoPedidos agregarProductoConNombre: 'Gaseosa' precio: 250.0 yCantidad: 1 para: 'Carlos'.
	
	self assert: (algoPedidos cantidadProductosEnPedidoDe: 'Carlos') equals: 2.
	
	algoPedidos actualizarProductoConNombre: 'Gaseosa' conCantidad: 3 para: 'Carlos'.
	
	self assert: (algoPedidos cantidadProductosEnPedidoDe: 'Carlos') equals: 4.! !
	| algoPedidos | 
	
	algoPedidos := AlgoPedidos new.
	algoPedidos crearPedidoParaRetirarPara: 'Tom√°s'.
	
	algoPedidos agregarProductoConNombre: 'Ensalada' precio: 200.0 yCantidad: 1 para: 'Tom√°s'.
	algoPedidos agregarCuponAPedidoDe: 'Tom√°s' conPorcentaje: 10. 
	
	self assert: (algoPedidos precioPedidoDe: 'Tom√°s') closeTo: (200*0.9) precision: 0.01. "-10%"! !
	| algoPedidos | 
	
	algoPedidos := AlgoPedidos new.
	algoPedidos crearPedidoParaRetirarPara: 'Julian'.

	algoPedidos agregarMenuConNombre: 'Menu jueves' precio: 200.0 yCantidad: 1 para: 'Julian'.
	algoPedidos agregarProductoConNombre: 'Ensalada' precio: 200.0 yCantidad: 2 para: 'Julian'.

	algoPedidos agregarCuponAPedidoDe: 'Julian' conValor: 15.
	
	self assert: (algoPedidos precioPedidoDe: 'Julian') equals: 600.0.! !
	| algoPedidos | 
	
	algoPedidos := AlgoPedidos new.
	algoPedidos crearPedidoParaRetirarPara: 'Pablo'.
	
	algoPedidos agregarMenuConNombre: 'Menu viernes' precio: 200.0 yCantidad: 1 para: 'Pablo'.
	algoPedidos agregarProductoConNombre: 'Gaseosa' precio: 250.0 yCantidad: 1 para: 'Pablo'.
	
	self assert: (algoPedidos precioPedidoDe: 'Pablo') closeTo: 450.0 precision: 0.1.! !
	| algoPedidos | 
	
	algoPedidos := AlgoPedidos new.
	algoPedidos crearPedidoParaRetirarPara: 'Martin'.

	algoPedidos agregarCuponAPedidoDe: 'Martin' conValor: 15. 	
	algoPedidos agregarProductoConNombre: 'Pizza' precio: 350.0 yCantidad: 1 para: 'Martin'.
	
	self assert: (algoPedidos precioPedidoDe: 'Martin') closeTo: 335.0 precision: 0.01.  "-15"
	
	algoPedidos removerCuponDePedidoDe: 'Martin'.

	self assert: (algoPedidos precioPedidoDe: 'Martin') closeTo: 350.0 precision: 0.01.! !
	| algoPedidos | 
	
	algoPedidos := AlgoPedidos new.
	algoPedidos crearPedidoParaRetirarPara: 'Eugenio'.
	
	algoPedidos agregarProductoConNombre: 'Milanesa' precio: 250.0 yCantidad: 2 para: 'Eugenio'.
	algoPedidos agregarProductoConNombre: 'Gelatina' precio: 100.0 yCantidad: 1 para: 'Eugenio'.
	 
	self assert: (algoPedidos precioPedidoDe: 'Eugenio') equals: 600.0.! !
	| algoPedidos | 
	
	algoPedidos := AlgoPedidos new.
	algoPedidos crearPedidoParaRetirarPara: 'Diego'.

	algoPedidos agregarCuponAPedidoDe: 'Diego' conValor: 15. 	
	algoPedidos agregarProductoConNombre: 'Milanesa' precio: 350.0 yCantidad: 1 para: 'Diego'.
	
	self assert: (algoPedidos precioPedidoDe: 'Diego') closeTo: 335.0 precision: 0.01. "-15"! !
	| algoPedidos | 
	
	algoPedidos := AlgoPedidos new.
	algoPedidos crearPedidoParaRetirarPara: 'Captain Falcon'.
	
	algoPedidos agregarProductoConNombre: 'Ramen' precio: 250.0 yCantidad: 2 para: 'Captain Falcon'.
	 
	self should: [algoPedidos agregarCuponAPedidoDe: 'Kirby' conPorcentaje: 10.] raise: PedidoNoEstaError.! !
	| algoPedidos | 
	
	algoPedidos := AlgoPedidos new.
	algoPedidos crearPedidoParaRetirarPara: 'Mateo'.
	
	algoPedidos agregarProductoConNombre: 'Coca' precio: 1000.0 yCantidad: 1 para: 'Mateo'.
	algoPedidos agregarProductoConNombre: 'Sprite' precio: 1500.0 yCantidad: 1 para: 'Mateo'.
	 
	self assert: (algoPedidos precioPedidoDe: 'Mateo') equals: 2500.0.! !
	| algoPedidos | 
	
	algoPedidos := AlgoPedidos new.
	algoPedidos crearPedidoParaRetirarPara: 'Fox'.

	algoPedidos agregarCuponAPedidoDe: 'Fox' conValor: 15. 	
	algoPedidos agregarProductoConNombre: 'Pizza' precio: 350.0 yCantidad: 1 para: 'Fox'.
	
	self should: [algoPedidos removerCuponDePedidoDe: 'Falco'.] raise: PedidoNoEstaError.
	

	! !
	| algoPedidos | 
	
	algoPedidos := AlgoPedidos new.
	algoPedidos crearPedidoParaRetirarPara: 'Captain Falcon'.
	
	algoPedidos agregarProductoConNombre: 'Ramen' precio: 250.0 yCantidad: 2 para: 'Captain Falcon'.
	 
	self should: [algoPedidos agregarCuponAPedidoDe: 'Kirby' conValor: 10.] raise: PedidoNoEstaError.! !
	| algoPedidos | 
	
	algoPedidos := AlgoPedidos new.
	algoPedidos crearPedidoParaRetirarPara: 'Captain Falcon'.
	
	algoPedidos agregarMenuConNombre: 'Menu Lunes' precio: 250.0 yCantidad: 2 para: 'Captain Falcon'.
	 
	self should: [algoPedidos agregarMenuConNombre: 'Menu Viernes' precio: 100.0 yCantidad: 1 para: 'Kirby'.] raise: PedidoNoEstaError.! !
	| algoPedidos | 
	
	algoPedidos := AlgoPedidos new.
	algoPedidos crearPedidoParaRetirarPara: 'Mateo'.
	
	algoPedidos agregarProductoConNombre: 'Coca' precio: 1000.0 yCantidad: 1 para: 'Mateo'.
	algoPedidos agregarProductoConNombre: 'Sprite' precio: 1500.0 yCantidad: 1 para: 'Mateo'.
	 
	self assert: (algoPedidos precioPedidoDe: 'Mateo') equals: 2500.0.! !
	| algoPedidos | 
	
	algoPedidos := AlgoPedidos new.
	algoPedidos crearPedidoParaRetirarPara: 'Julian'.

	algoPedidos agregarMenuConNombre: 'Menu jueves' precio: 200.0 yCantidad: 1 para: 'Julian'.

	algoPedidos agregarCuponAPedidoDe: 'Julian' conPorcentaje: 15.
	
	self assert: (algoPedidos precioPedidoDe: 'Julian') equals: 200.0.! !
	| algoPedidos | 
	
	algoPedidos := AlgoPedidos new.
	algoPedidos crearPedidoParaRetirarPara: 'Captain Falcon'.
	
	algoPedidos agregarProductoConNombre: 'Ramen' precio: 250.0 yCantidad: 2 para: 'Captain Falcon'.
	 
	self should: [algoPedidos agregarProductoConNombre: 'Gelatina' precio: 100.0 yCantidad: 1 para: 'Kirby'.] raise: PedidoNoEstaError.! !
	| algoPedidos | 
	
	algoPedidos := AlgoPedidos new.
	algoPedidos crearPedidoParaRetirarPara: 'Martin'.
	algoPedidos agregarCuponAPedidoDe: 'Martin' conPorcentaje: 10.

	
	algoPedidos agregarProductoConNombre: 'Pizza' precio: 200 yCantidad: 1 para: 'Martin'.
	algoPedidos agregarCuponAPedidoDe: 'Martin' conValor: 10. 	
	
	self assert: (algoPedidos precioPedidoDe: 'Martin') closeTo: 190 precision: 0.01.! !
	| algoPedidos | 
	
	algoPedidos := AlgoPedidos new.
	algoPedidos crearPedidoParaRetirarPara: 'Martin'.

	algoPedidos agregarCuponAPedidoDe: 'Martin' conValor: 15. 	
	algoPedidos agregarProductoConNombre: 'Pizza' precio: 200 yCantidad: 1 para: 'Martin'.
	
	algoPedidos agregarCuponAPedidoDe: 'Martin' conPorcentaje: 10.

	self assert: (algoPedidos precioPedidoDe: 'Martin') closeTo: 180 precision: 0.01.! !
	| algoPedidos | 
	
	algoPedidos := AlgoPedidos new.
	algoPedidos crearPedidoParaRetirarPara: 'Mario'.
	
	self should: [algoPedidos agregarMenuConNombre: 'Menu generico' precio: -250.0 yCantidad: 1 para: 'Mario'.] raise: ValorInvalidoError.! !
	| algoPedidos | 
	
	algoPedidos := AlgoPedidos new.
	algoPedidos crearPedidoParaRetirarPara: 'Mario'.
	
	self should: [algoPedidos agregarProductoConNombre: 'Milanesa' precio: 250.0 yCantidad: -1 para: 'Mario'.] raise: ValorInvalidoError.! !
	| algoPedidos | 
	
	algoPedidos := AlgoPedidos new.
	algoPedidos crearPedidoParaRetirarPara: 'Mario'.
	
	self should: [algoPedidos agregarMenuConNombre: 'Menu generico' precio: -250.0 yCantidad: 1 para: 'Mario'.] raise: ValorInvalidoError.! !