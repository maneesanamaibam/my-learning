

function traverseObj(obj) {
  if (Object.keys(obj).length === 0) return

  const isObjectType = (val) => { return val instanceof Object && Object.prototype.toString.call(val) === '[object Object]' }
  const isArrayType = (val) => { return Array.isArray(val) }

  const TAB = ' '.repeat(3)

  const weakMap = new WeakMap();
  const openCloseObjTracKMap = new Map();

  const q = []
  console.log('{')
  for (const key of Object.keys(obj)) {
    // console.log('VISITING KEY: ', key, ' => ', 'Value: ', obj[key])
    q.push(key)
  }
  weakMap.set(obj, true)
  let parent = obj;
  let currentObjOpeningKey;
  let currentObjClosingKey;
  while (q.length > 0) {
    const frontKey = q.shift();
    if (isObjectType(parent[frontKey])) {
      // const 
      if (weakMap.has(parent[frontKey])) { // detected circular reference 
        continue
      }
      const currObjKeys = Object.keys(parent[frontKey])
      currentObjOpeningKey = currObjKeys.length > 0 ? currObjKeys[0] : -1;
      currentObjClosingKey = currObjKeys.length > 0 ? currObjKeys[currObjKeys.length - 1] : -1
      openCloseObjTracKMap.set(parent[frontKey], [currentObjOpeningKey, currentObjClosingKey]) // object_reference => opening key and closing key
      for (const key of currObjKeys) {
        // console.log(key, ' => ', 'Value: ', parent[frontKey][key])
        q.push(key)
      }
      parent = parent[frontKey]
    } else {
      console.log(TAB, frontKey, ': ', parent[frontKey])

    }
  }
  console.log('}')
}


function traverseDFSObj(obj) {
  if (Object.keys(obj).length === 0) return
  const stack = []
  const isObjectType = (val) => { return val instanceof Object && Object.prototype.toString.call(val) === '[object Object]' }
  const isArrayType = (val) => { return Array.isArray(val) }
  const TAB = ' '.repeat(2)
  const toArrayStrUtil = (arr) => {
    let arrStr = '['
    for (let i = 0; i < arr.length; i++) {
      ((i != arr.length - 1 ? (arrStr += `${arr[i]},`) : (arrStr += `${arr[i]}`)))
    }
    arrStr += ']'
    return arrStr
  }

  const logKeyValueUtil = (tabSpace, key, val) => {
    const valStr = typeof val === 'string' ? `"${val}"` : val
    console.log(tabSpace, key, ' : ', valStr, ',')
  }
  let parent = obj
  let objCount = 0;
  let globalObjCount = 0;

  const weakMap = new WeakMap();
  weakMap.set(obj, true)

  console.log('{')
  const rootLevelNonObjKeys = []

  for (const key of Object.keys(obj)) {
    if (isObjectType(obj[key])) {
      stack.push(key)
      parent = obj;
      objCount = 0;
      while (stack.length) {
        const topKey = stack.shift()
        if (isObjectType(parent[topKey])) {

          if (weakMap.has(parent[topKey])) { // detected circular reference 
            console.log(TAB.repeat(objCount), topKey, ': [Circular Object]')
            continue
          }

          let localObjCount = 0;
          const currObjKeys = Object.keys(parent[topKey])

          objCount++;
          globalObjCount++;
          weakMap.set(parent[topKey], true)

          console.log(TAB.repeat(objCount), topKey, ': {')

          for (const key of currObjKeys) {
            const tempObj = parent[topKey][key]
            if (isObjectType(tempObj)) {
              stack.unshift(key)
              localObjCount++
            } else if (isArrayType(tempObj)) {
              let arrStr = toArrayStrUtil(tempObj)
              console.log(TAB.repeat(objCount + 1), key, ' : ', arrStr, ',')
            }
            else {
              logKeyValueUtil(TAB.repeat(objCount + 1), key, tempObj)
            }
          }

          if (localObjCount == 0) {
            console.log(TAB.repeat(objCount), '},')
            objCount--
            globalObjCount--
          }
          parent = parent[topKey]
        }
      }
    } else if (isArrayType(obj[key])) {
      // Array type
      const arrStr = toArrayStrUtil(obj[key])
      console.log(TAB, key, ' : ', arrStr, ',')
    } else {
      rootLevelNonObjKeys.push(key)
    }
  }

  for (let i = globalObjCount; i > 0; i--) {
    console.log(TAB.repeat(i), '},')
  }

  for (const nk of rootLevelNonObjKeys) {
    const objVal = weakMap.has(obj[nk]) ? '[Circular Object]' : obj[nk]
    logKeyValueUtil(TAB, nk, objVal)
  }
  console.log('}')
}
function main() {
  const testObj = {
    foo0: 'bar0',
    fooInner0: {
      foo1: 'bar_1',
      fooInner1: {
        foo2: 'bar_2',
        fooInner2: {
          foo3: 'bar_3',
          fooInner3: {
            foo4: 'bar_4',
            fooInner4: {
              foo5: 'bar_5' // 6 Levels
            }
          }
        }
      }

    }
  }
  // const greenStatusUnicode = '\u1F7E2'

  // console.log(greenStatusUnicode, '[SUCESSS] Success info message')
  testObj.self = testObj
  // traverseObj(testObj)
  traverseDFSObj(testObj)
  const tObj_1 = {
    name_1: 'value_1',
    root_arr_example: [1, 3, 43, 4, 45, 5, 5],
    obj_1: {
      name_2: 'value_2'
    },
    obj_2: {
      name_3: 'value_3',
      arr_example: [1, 3, 43, 4, 45, 5, 5]
    }


  }
  traverseDFSObj(tObj_1)
}



main()
