package Java.ProdCons;

import java.util.ArrayList;

public class Buffer{

    /* TODO
     *  Funciones: 
     *      -> Add
     *      -> Pop
     *    X -> Liberar (No se puede) 
     *    - -> ComprobarLLeno (No necesaria)
     *    - -> ComprobarVacio (No necesaria)
     *      -> AccederElementoPosicion
     *    - -> ObtenerNumElementos (No necesaria) 
     */

    private ArrayList<Integer> aBuffer;
    private int iRemIndex, iAddIndex;
    private boolean bFull, bEmpty;
    private int iMaxSize;
    
    // ========== CONSTRUCTOR ==========
    public Buffer(int imaxsize){
        aBuffer = new ArrayList<Integer>();
        iRemIndex = 0;
        iAddIndex = 0;
        bFull = false;
        bEmpty = true;
        iMaxSize = imaxsize;
    }
    // ========== FUNCIONES ==========

    public boolean ComprobarLLeno(Buffer iBuf){
        bFull = iBuf.aBuffer.size() == iMaxSize; 
        return bFull;
    }

    public boolean ComprobarVacio(Buffer iBuf){
        bEmpty = iBuf.aBuffer.size() == 0;
        return bEmpty;
    }

    public boolean Add(Buffer iBuf,Integer iElemento){
        boolean bValidacion = true;
        if(!ComprobarLLeno(iBuf)){
            iBuf.aBuffer.add(iElemento);
            iBuf.iAddIndex = (iBuf.iAddIndex+1)%iBuf.iMaxSize;
        } else {
            bValidacion = false;
        }
        return bValidacion;
    }

    public Integer Pop(Buffer iBuf){
        Integer iValidacion;
        if(!ComprobarVacio(iBuf)){
             iValidacion = iBuf.aBuffer.get(iRemIndex);
            iBuf.iRemIndex = (iBuf.iRemIndex+1)%iBuf.iMaxSize;
        } else {
            iValidacion = null;
        }
        return iValidacion;
    }

    public Integer AccederElementoPosicion(Buffer iBuf,int iPosicion){
        Integer iElemento;
        if(!ComprobarVacio(iBuf)){
            iElemento = iBuf.aBuffer.get(iPosicion);
        } else {
            iElemento = null;
        }
        return iElemento;
    }

    public Integer numElementos(Buffer iBuf){
        Integer numElementos = iBuf.aBuffer.size();
        return numElementos;
    }
}