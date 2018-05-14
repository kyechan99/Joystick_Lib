/*********************************************************************
* Date : 2018.05.14
* Name : JoystickManager
* Description : Joystick (Unity 2018.01)
* Link : https://github.com/kyechan99/Joystick_Lib
***********************************************************************/

using UnityEngine;
using System.Collections;

public class JoystickManager : MonoBehaviour
{
    [SerializeField]
    private GameObject _joystick;
    [SerializeField]
    private GameObject _joystickLimit;

    [SerializeField]
    private GameObject _player;

    [SerializeField]
    private Camera _cam;

    Vector2 _touchPos;
    bool _canMove = false;
    public float _speed = 0.1f;
    public float _limitSize = 0.9f;		// joystick Limit Move Size


    void Update()
    {
        if (Input.GetMouseButtonUp(0))
        {
            _joystick.transform.position = _joystickLimit.transform.position;
            _canMove = false;
        }
        else if (Input.GetMouseButton(0))
        {
            _touchPos = _cam.ScreenToWorldPoint(Input.mousePosition);

            if (_canMove)
            {
                joystickControl();

                float moveX = _joystick.transform.position.x - _joystickLimit.transform.position.x;
                float moveY = _joystick.transform.position.y - _joystickLimit.transform.position.y;

                Vector3 temp = _player.transform.position;
                temp.x += moveX * _speed;
                temp.y += moveY * _speed;

                _player.transform.position = temp;

                temp = _cam.transform.position;
                temp.x += moveX * _speed;
                temp.y += moveY * _speed;
                _cam.transform.position = temp;
            }
            else
            {
                Vector2 wp = _cam.ScreenToWorldPoint(Input.mousePosition);
                Ray2D ray = new Ray2D(wp, Vector2.zero);

                RaycastHit2D hit = Physics2D.Raycast(ray.origin, ray.direction);

                if (hit.collider != null)
                {
                    if (hit.collider.gameObject.CompareTag(_joystick.tag))
                    {
                        _canMove = true;
                    }
                }
            }
        }
    }

    bool isTouchCircle(Vector2 pos, Vector2 center, float radius)
    {
        float dx = (pos.x - center.x);
        float dy = (pos.y - center.y);
        return (radius >= Mathf.Sqrt((dx * dx) + (dy * dy)));
    }

    void joystickControl()
    {
        if (!(isTouchCircle(_touchPos, _joystickLimit.transform.position, _limitSize)))
        {
            float dX = _touchPos.x - _joystickLimit.transform.position.x;
            float dY = _touchPos.y - _joystickLimit.transform.position.y;

            float distance = Mathf.Sqrt(dX * dX + dY * dY);
            float angle = Mathf.Atan2(dY, dX);

            if (distance > _limitSize)
            {
                dX = Mathf.Cos(angle) * _limitSize;
                dY = Mathf.Sin(angle) * _limitSize;

                _touchPos.x = _joystickLimit.transform.position.x + dX;
                _touchPos.y = _joystickLimit.transform.position.y + dY;
            }

            _joystick.transform.position = _touchPos;
        }
        else
        {
            _joystick.transform.position = _touchPos;
        }
    }
}
