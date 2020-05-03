
/**
 * Actor is the parent class to all game objects.
*/
namespace Game
{
    class Actor {
        public:
            virtual void MoveForward() = 0;
            virtual void MoveBackward()= 0;
            virtual void MoveRight()= 0;
            virtual void MoveLeft() = 0;
            virtual void MoveUp() = 0;
            virtual void MoveDown() = 0;
            virtual void TrunRight() = 0;
            virtual void TrunLeft() = 0;
            virtual void TrunUp() = 0;
            virtual void TrunDown() = 0;
            virtual void Attack() = 0;
    };
} // namespace Game
